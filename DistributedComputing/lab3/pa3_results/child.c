#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "ipc.h"
#include "io.h"
#include "pa2345.h"
#include "child.h"
#include "banking.h"
#include "lamport_time.h"

#define BALANCE_HIST_SIZE(hist) \
 (sizeof(BalanceHistory) - (sizeof(hist->s_history) - hist->s_history_len))


/** Syncronization cycle.
 */
static void
sync_state(proc_t *p, MessageType type, char *payload, size_t payload_len) {
    Message msg;

    increase_lamport_time();
    msg.s_header = (MessageHeader) {
            .s_magic       = MESSAGE_MAGIC,
            .s_payload_len = payload_len,
            .s_type        = type,
            .s_local_time  = get_lamport_time()
    };
    memcpy(msg.s_payload, payload, payload_len);
    send_multicast((void*)p, (const Message *)&msg);

    for (size_t i = 1; i <= p->procnum; i++) {
       if (i != p->self_id) {
           while(receive((void*)p, i, &msg) != 0){};
           set_lamport_time(msg.s_header.s_local_time);
           if (msg.s_header.s_type != type) {
                fprintf(stderr, "ID %d waited for %d, but got %d.\n",
                                p->self_id, type, msg.s_header.s_type);
           }
       }
    }
}

static void
send_balance(proc_t *p, char *payload, size_t payload_len) {
    Message msg;

    increase_lamport_time();
    msg.s_header = (MessageHeader) {
            .s_magic       = MESSAGE_MAGIC,
            .s_payload_len = payload_len,
            .s_type        = BALANCE_HISTORY,
            .s_local_time  = get_lamport_time()
    };
    memcpy(msg.s_payload, payload, payload_len);
    send((void*)p, PARENT_ID, &msg);
}

/* Copy balance if there was no transfer on the <time>. */
static void
copy_range(BalanceHistory *history, uint8_t time) {
    uint8_t min = history->s_history_len;
    BalanceState template = history->s_history[min-1];
    for (uint8_t i = min; i <= time; i++) {
        history->s_history[i] = template;
        history->s_history[i].s_time = i;
    }
    history->s_history_len = time + 1;
}

static void
update_balance(BalanceHistory *history, balance_t amount) {
    timestamp_t t = get_lamport_time();
    uint8_t hlen  = history->s_history_len;
    balance_t bal = history->s_history[hlen-1].s_balance;
    balance_t bpi = history->s_history[hlen-1].s_balance_pending_in;

    copy_range(history, (uint8_t)t);
    history->s_history[t] = (BalanceState) {
            .s_balance = bal + amount,
            .s_time = t,
            .s_balance_pending_in = bpi - amount
    };

    history->s_history_len = t+1;
}

/** Add to the history new records about balance changing.
 * 
 * @param sign_balance  If the value is positive balance increases
 *                      and decreases otherwise.
 */
static void
send_transfer(proc_t *p, TransferOrder *order) {
    Message msg;
    msg.s_header = (MessageHeader) {
        .s_magic       = MESSAGE_MAGIC,
        .s_payload_len = sizeof(TransferOrder),
        .s_type        = TRANSFER,
        .s_local_time  = get_lamport_time()
    };
    memcpy(msg.s_payload, order, sizeof(TransferOrder));
    send((void *)p, order->s_dst, &msg);
}

static void
send_ack(proc_t *p) {
    Message msg;
    msg.s_header = (MessageHeader) {
        .s_magic       = MESSAGE_MAGIC,
        .s_payload_len = 0,
        .s_type        = ACK,
        .s_local_time  = get_lamport_time()
    };
    send((void *)p, PARENT_ID, &msg);
}

/** Transfer cycle.
 * 
 * @algo
 *      (1) if self_id == src then (2)
 *          else if self_id == dst then (3)
 *          else (4)
 *      (2) Decrease balance and send TRANSFER to dst.
 *      (3) Increase balance and send ASK to PARENT_ID.
 *      (4) Do nothing.
 */
static void
transfer_handle(proc_t *p, BalanceHistory *history, TransferOrder *order) {

    increase_lamport_time();
    if (p->self_id == order->s_src) {
        update_balance(history, -order->s_amount);
        send_transfer(p, order);

        fprintf(p->io->events_log_stream, log_transfer_out_fmt,
                get_lamport_time(), p->self_id,
                order->s_amount, order->s_dst);
        fflush(p->io->events_log_stream);


    } else if (p->self_id == order->s_dst) {
        update_balance(history, order->s_amount);

        fprintf(p->io->events_log_stream, log_transfer_in_fmt,
                get_lamport_time(), p->self_id,
                order->s_amount, order->s_dst);
        fflush(p->io->events_log_stream);
        send_ack(p);
    } else {
        fprintf(p->io->events_log_stream, "ID %d got mesasge for %d and %d.\n",
                p->self_id, order->s_src, order->s_dst);
        fflush(p->io->events_log_stream);
    }
    
}

static void
work(proc_t *p, BalanceHistory *history) {
    while (true) {
        Message msg = {{ 0 }};
        if (receive_any(p, &msg) < 0)
            continue;

        set_lamport_time(msg.s_header.s_local_time);

        switch (msg.s_header.s_type) {
            case TRANSFER: {
                fflush(p->io->events_log_stream);
                transfer_handle(p, history, (TransferOrder*)(msg.s_payload));
                break;
            }
            case STOP:
                fflush(p->io->events_log_stream);
                /* Maybe, need to chack if there are any TRANSFER messages*/
                return;
            default: {
                fprintf(p->io->pipes_log_stream,
                        "ID %d got wrong message with type %d.\n",
                        p->self_id, msg.s_header.s_type);
                fflush(p->io->events_log_stream);
                continue;
            }
        }
    }
}

/** Child main function.
 */ 
int
child(proc_t *p, balance_t balance) {
    size_t len;
    char payload[MAX_PAYLOAD_LEN];
    const IO *io = p->io;
    BalanceHistory history = {
        .s_id = p->self_id,
        .s_history_len = 0,
        .s_history = {{ 0 }}
    };

    history.s_history[0] = (BalanceState) {
        .s_balance = balance,
        .s_time = 0,
        .s_balance_pending_in = 0
    };
    history.s_history_len++;

    close_unsed_fds(p->io, p->self_id, p->procnum);
    /* Process starts. */
    len = sprintf(payload, log_started_fmt, 
                  get_lamport_time(), p->self_id, getpid(),
                  getppid(), history.s_history[0].s_balance);
    fputs(payload, io->events_log_stream); 
    fflush(p->io->events_log_stream);

    /* Proces sync with others. */
    sync_state(p, STARTED, payload, len);
    fprintf(io->events_log_stream, log_received_all_started_fmt,
            get_lamport_time(), p->self_id);
    fflush(p->io->events_log_stream);

    /* Work. */
    work(p, &history);

    /* Process's done. */
    uint8_t hl  = history.s_history_len;
    balance_t b = history.s_history[hl-1].s_balance;
    len = sprintf(payload, log_done_fmt, get_lamport_time(), p->self_id, b);
    fputs(payload, io->events_log_stream); 
    fflush(p->io->events_log_stream);

    /* Process syncs wih ohers. */
    sync_state(p, DONE, payload, len);
    fprintf(io->events_log_stream, log_received_all_done_fmt, 
            get_lamport_time(), p->self_id);
    fflush(p->io->events_log_stream);

    copy_range(&history, get_lamport_time());

    send_balance(p,(char*)&history, sizeof(history.s_history[0]) * history.s_history_len);
    return 0;
}
