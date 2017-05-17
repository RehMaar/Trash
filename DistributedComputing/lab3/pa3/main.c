#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "ipc.h"
#include "pa2345.h"
#include "child.h"
#include "banking.h"
#include "lamport_time.h"

#define BALANCES_ARG_OFFSET     3

static inline local_id
get_options(int argc, char *argv[], balance_t *balances) {
    size_t pnum = 0;
    switch(getopt(argc, argv, "p:")) {
        case 'p': {
            char *endptr = NULL;
            pnum = strtol(optarg, &endptr, 10);   
            if (optarg == endptr || pnum > MAX_PROC || pnum <= 0) {
                return 0;
            }
            break;
        }
        default:
            return 0;
    }
    if (argc - BALANCES_ARG_OFFSET != pnum)
        return 0;

    for (size_t i = 0; i < pnum; i++) {
        char *endptr = NULL;
        char *str = argv[i+BALANCES_ARG_OFFSET];
        balances[i] = strtol(str, &endptr, 10);
        if (str == endptr || balances[i] < 0)
            return 0;
    }
    
    return (local_id)pnum;
}

static void
send_stop(proc_t *p) {
    Message msg;
    increase_lamport_time();
    msg.s_header = (MessageHeader){
        .s_magic       = MESSAGE_MAGIC,
        .s_payload_len = 0,
        .s_type        = STOP,
        .s_local_time  = get_lamport_time(),
    };
    send_multicast((void*)p, &msg);
}

static void
wait_balance_from_all(proc_t *p, AllHistory *all_history) {
    Message msg = {{ 0 }};
    local_id i = 1;

    while (i <= p->procnum) {
        while(receive((void*)p, i, &msg) != 0);

        set_lamport_time(msg.s_header.s_local_time);

        if (msg.s_header.s_type == BALANCE_HISTORY) {
            memcpy(&all_history->s_history[i-1], &msg.s_payload, 
                   msg.s_header.s_payload_len);
            i++;
        }
    }
    all_history->s_history_len = p->procnum;
}

static void
wait_msg_from_all(proc_t *p, MessageType type) {
    Message msg = { {0} };
    for (local_id i = 1; i <= p->procnum; i++) {
        while(receive((void*)p, i, &msg) != 0);
        set_lamport_time(msg.s_header.s_local_time);
        if (msg.s_header.s_type != type) {
            fprintf(p->io->pipes_log_stream, 
                    "Bad received message: waited for %d, but got %d.\n",
                    type, msg.s_header.s_type);
        }
    }
}


static void
main_cycle(proc_t *p) {
    AllHistory all_history = { 0 };
    const IO *io = p->io;

    wait_msg_from_all(p, STARTED);
    fprintf(io->events_log_stream, log_received_all_started_fmt, 
            get_lamport_time(), PARENT_ID);
    fflush(p->io->events_log_stream);

    bank_robbery((void*)p, p->procnum);

    send_stop(p);

    wait_msg_from_all(p, DONE);
    fprintf(io->events_log_stream, log_received_all_done_fmt,
            get_lamport_time(), PARENT_ID);
    fflush(p->io->events_log_stream);

    wait_balance_from_all(p, &all_history);
//    for (uint8_t i = 0; i < all_history.s_history_len; i++) {
//        BalanceHistory history = all_history.s_history[i];
//        fprintf(stderr, "ID %d hlen %d\n", history.s_id, history.s_history_len);
//        fflush(stderr);
//    }

    print_history(&all_history);
    while(wait(NULL) > 0);
}


int
main(int argc, char *argv[]) {
#define TRY_FOPEN(expr)  \
    if ((expr)== NULL) { \
        perror("fopen"); \
        return -1;       \
    }

    IO io = { 0 };
    proc_t proc = (proc_t){ 
        .io = &io
    };
    /* Get balance from arguments. */
    balance_t balances[MAX_PROCESS_ID] = { 0 };
    if ((proc.procnum = get_options(argc, argv, (balance_t*)balances)) == 0) {
        fputs("Bad arguments.\n", stderr);
        return -1;
    }
    
    /* Try open log files. */
    TRY_FOPEN(io.events_log_stream = fopen(events_log, "w+"))
    TRY_FOPEN(io.pipes_log_stream  = fopen(pipes_log, "w"))

    if (create_pipes(&io, proc.procnum) < 0)
        return -1;

    /* Create child processes. */
    for (int i = 1; i <= proc.procnum; i++) {
        pid_t pid = fork();
        if (0 > pid) {
            exit(EXIT_FAILURE);
        } else if (0 == pid) {
            /* Child. */
            proc.self_id = i;
            int ret = child(&proc, balances[i-1]);
            exit(ret);
        }
    }
    close_unsed_fds(&io, PARENT_ID, proc.procnum);

    proc.self_id = PARENT_ID;
    main_cycle(&proc);

    fclose(io.pipes_log_stream);
    fclose(io.events_log_stream);
    return 0;
}
