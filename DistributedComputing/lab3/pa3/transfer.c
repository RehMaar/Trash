#include <stdio.h>
#include <string.h>

#include "banking.h"
#include "lamport_time.h"

void
transfer(void * parent_data, local_id src, local_id dst,
              balance_t amount)
{
    Message msg;

    increase_lamport_time();
    msg.s_header = (MessageHeader) {
        .s_magic       = MESSAGE_MAGIC,
        .s_payload_len = sizeof(TransferOrder),
        .s_type        = TRANSFER,
        .s_local_time  = get_lamport_time()
    };

    TransferOrder order = (TransferOrder) {
        .s_src = src,
        .s_dst = dst,
        .s_amount = amount
    };

    memcpy(msg.s_payload, &order, sizeof(TransferOrder));

#ifdef DEBUG
    fprintf(stderr, "%d: procces 0 initiate trasmission (%d -- %d).\n",
            get_lamport_time(), src, dst);
#endif
    send(parent_data, src, &msg);

    while (receive(parent_data, dst, &msg));
    set_lamport_time(msg.s_header.s_local_time);

#ifdef DEBUG
    fprintf(stderr, "%d: process 0 received ACK from %d.\n",
            get_lamport_time(), dst);
#endif
}
