#define _DEFAULT_SOURCE
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

#include "io.h"
#include "ipc.h"
#include "child.h"

int
send(void *self, local_id dst, const Message *msg) {
    proc_t *p   = (proc_t*)self;
    local_id src  = p->self_id;

    if (src == dst)
        return -1;

    int    fd   = p->io->fds[src][dst][WRITE_FD];
    int ret = write(fd, msg, sizeof(MessageHeader) + msg->s_header.s_payload_len);
    fprintf(p->io->events_log_stream, "%d: ID %hhd send %d bytes to %d.\n", get_lamport_time(), src, ret, dst);
    fflush(p->io->events_log_stream);
    return 0;
}

int
send_multicast(void *self, const Message *msg) {
    proc_t   *p   = (proc_t*)self;
    local_id   pnum = p->procnum;

    for (local_id i = 0; i <= pnum; i++) {
        send(self, i, msg);
    }
    return 0;
}

int
receive(void *self, local_id from, Message *msg) {
    proc_t *p   = (proc_t*)self;
    local_id to = p->self_id;
    if (to == from)
        return -1;
    int    fd   = p->io->fds[from][to][READ_FD];
    ssize_t r = read(fd, msg, sizeof(Message));
    if (r < 0 && errno != EAGAIN) {
        perror("read");
        return -1;
    }
    if (r > 0) {
        fprintf(p->io->events_log_stream, "%d: ID %d got %zd bytes from %d with local_time %d.\n", get_lamport_time(), to, r, from, msg->s_header.s_local_time);
        fflush(p->io->events_log_stream);
    }

    return r > 0 ? 0 : -1;
}

int
receive_any(void *self, Message *msg) {
    proc_t *p = (proc_t*)self;
    local_id pnum = p->procnum;

    for (local_id i = 0; i <= pnum; i++) {
        if (receive(self, i, msg) == 0)
            return 0;
    }
    return -1;   
}
