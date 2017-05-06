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

    size_t pnum = p->io->procnum;
    int    fd   = p->io->fds[INDEX(src, dst,pnum)].w;
    return write(fd, msg, sizeof(Message));
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
    proc_t *p   = (proc_t*)self;
    local_id to = p->self_id;

    if (to == from)
        return -1;

    size_t pnum = p->io->procnum;
    int    fd   = p->io->fds[INDEX(from, to,pnum)].r;

    return read(fd, msg, sizeof(Message)) > 0 ? 0 : -1;
}

int
receive_any(void *self, Message *msg) {
    proc_t *p   = (proc_t*)self;
    size_t pnum = p->io->procnum;

    for (size_t i = 1; i <= pnum; i++) {
        if (receive(p, (local_id)i, msg) == 0)
            return 0;
    }

    return -1;   
}
