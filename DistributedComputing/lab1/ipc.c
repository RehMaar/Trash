#include <unistd.h>
#include <stdbool.h>

#include "io.h"
#include "ipc.h"
#include "child.h"

int
send(void *self, local_id dst, const Message *msg) {
    proc_t   *p   = (proc_t*)self;
    local_id src  = p->self_id;
    size_t   pnum = p->io->procnum;

    int      fd   = p->io->fds[INDEX(src, dst,pnum)][WRITE_FD];
    return src == dst ? -1 : write(fd, msg, sizeof(Message));
}

int
send_multicast(void *self, const Message *msg) {
    proc_t   *p   = (proc_t*)self;
    size_t   pnum = p->io->procnum;
    for (size_t i = 0; i <= pnum; i++) {
        send((void*)p, (local_id)i, msg);
    }
    return 0;
}

int
receive(void *self, local_id from, Message *msg) {
    proc_t   *p   = (proc_t*)self;
    local_id to   = p->self_id;
    size_t   pnum = p->io->procnum;
    int      fd   = p->io->fds[INDEX(from, to,pnum)][READ_FD];
    return to == from ? -1 : read(fd, msg, sizeof(Message)) > 0 ? 0 : -1;
}

int
receive_any(void *self, Message *msg) {
    proc_t *p   = (proc_t*)self;
    size_t pnum = p->io->procnum;
    for (size_t i = 0; i < pnum; i++) {
        if (receive(p, (local_id)(i+1), msg) == 0)
            return 0;
    }
    return -1;   
}
