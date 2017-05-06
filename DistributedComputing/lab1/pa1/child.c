#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "ipc.h"
#include "io.h"
#include "pa1.h"
#include "child.h"


/** Close unused file descriptors.
 * 
 * @param fds   Array of pipes' descriptors.
 * @param id    ID of the child process.
 * @param num   Number of processes.
 * 
 */ 
void
close_unsed_fds(IO *io, local_id id) {

    for (size_t i = 0; i <=io->procnum; i++) {
        if (i != id) {
            fprintf(stderr, "ID %d closes r(%lu) w(%lu)\n", id, INDEX(id,i,io->procnum), INDEX(i,id,io->procnum));
            close(io->fds[INDEX(id,i, io->procnum)][READ_FD]);
            close(io->fds[INDEX(i,id, io->procnum)][WRITE_FD]);
        }
    }

    for (size_t i = 0; i <= io->procnum; i++) {
        for (size_t j = 0; j <= io->procnum; j++) {
            if (i != j && i != id && j != id) {
                fprintf(stderr, "ID %d closes %zu\n", id, INDEX(i, j, io->procnum));
                close(io->fds[INDEX(i, j, io->procnum)][WRITE_FD]);
                close(io->fds[INDEX(i, j, io->procnum)][READ_FD]);
            }
        }
    }
}

/** Syncronization cycle.
 */
static void
sync(proc_t *p, MessageType type, char *payload, size_t payload_len) {
    Message msg;
    msg.s_header = (MessageHeader) {
            .s_magic       = MESSAGE_MAGIC,
            .s_payload_len = payload_len,
            .s_type        = type,
            .s_local_time  = 0
    };
    strncpy(msg.s_payload, payload, payload_len);

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
 */ 
int
child(IO *io, local_id id) {

    proc_t p;
    char payload[MAX_PAYLOAD_LEN];
    size_t len;
    p = (proc_t){
        .io      = io,
        .self_id = id
    };

    close_unsed_fds(io, id);
    /* Process starts. */
    len = sprintf(payload, log_started_fmt, id, getpid(), getppid());
    fputs(payload, io->events_log_stream); 
    /* Proces sync with others. */
    sync(&p, STARTED, payload, len);

    fprintf(io->events_log_stream, log_received_all_started_fmt, id);
    /* Work. */
    /* Process's done. */
    len = sprintf(payload, log_done_fmt, id);
    fputs(payload, io->events_log_stream); 
    /* Process syncs wih ohers. */
    sync(&p, DONE, payload, len);
    fprintf(io->events_log_stream, log_received_all_done_fmt, id);

    return 0;
}
