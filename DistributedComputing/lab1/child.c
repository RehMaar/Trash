#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "ipc.h"
#include "io.h"
#include "pa1.h"
#include "child.h"

#define READ        0
#define WRITE       1

/** Close unused file descriptors.
 * 
 * @param fds   Array of pipes' descriptors.
 * @param id    ID of the child process.
 * @param num   Number of processes.
 * 
 * @algo
 * 
 */ 
static void
close_unsed_fds(IO *io, local_id id) {
    for (size_t i = 0; i < io->procnum; i++) {
        if (i != id) {
            close(io->fds[INDEX(id,i, io->procnum)][READ_FD]);
            close(io->fds[INDEX(i,id, io->procnum)][WRITE_FD]);
        }
    }
}

/** Syncronization cycle.
 */
static void
sync(proc_t *p, MessageType type) {
    Message msg;
    msg.s_header = (MessageHeader) {
            .s_magic       = MESSAGE_MAGIC,
            .s_payload_len = 0,
            .s_type        = type,
            .s_local_time  = 0
    };
    send_multicast((void*)p, (const Message *)&msg);
    size_t get = p->io->procnum-1;
    while (get) {
        if (receive_any((void*)p, &msg) == 0) {
            get--;
        }
    }
}

/** Child main function.
 * 
 * @param fds   Array of pipes' descriptors.
 * @param id    ID of the child process.
 * @param num   Number of processes.
 * 
 */ 
int
child(IO *io, local_id id) {

    proc_t p;
    p = (proc_t){
        .io      = io,
        .self_id = id
    };

    close_unsed_fds(io, id);
    /* Process starts. */
    fprintf(io->events_log_stream, log_started_fmt, id, getpid(), getppid()); 
    /* Proces sync with others. */
    sync(&p, STARTED);
    fprintf(io->events_log_stream, log_received_all_started_fmt, id);
    /* Work. */
    /* Process's done. */
    fprintf(io->events_log_stream, log_done_fmt, id);
    /* Process syncs wih ohers. */
    sync(&p, DONE);
    fprintf(io->events_log_stream, log_received_all_done_fmt, id);

    return 0;
}
