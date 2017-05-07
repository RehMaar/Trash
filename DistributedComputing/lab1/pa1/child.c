#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
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

    for (local_id i = 0; i <= io->procnum; i++) {
        for (local_id j = 0; j <= io->procnum; j++) {
            if (i != j) {
                if (i == id) {
                    close(io->fds[i][j][READ_FD]);
                    fprintf(io->pipes_log_stream, "ID %d closes read(%hhd -- %hhd)\n", id, i,j);
                }

                if (j == id) {
                    close(io->fds[i][j][WRITE_FD]);
                    fprintf(io->pipes_log_stream, "ID %d closes write(%hhd -- %hhd)\n", id, i,j);
                }

                if (i != id && j != id) {
                    fprintf(io->pipes_log_stream, "ID %d closes pipe(%hhd -- %hhd)\n", id, i,j);
                    close(io->fds[i][j][WRITE_FD]);
                    close(io->fds[i][j][READ_FD]);
                }
            }
        }
    }

    fprintf(io->pipes_log_stream, "ID %d closes all fds.\n", id);
}


/** Syncronization cycle.
 */
static void
sync_state(proc_t *p, MessageType type, char *payload, size_t payload_len) {
    Message msg;
    msg.s_header = (MessageHeader) {
            .s_magic       = MESSAGE_MAGIC,
            .s_payload_len = payload_len,
            .s_type        = type,
            .s_local_time  = 0
    };
    strncpy(msg.s_payload, payload, payload_len);

    send_multicast((void*)p, (const Message *)&msg);
    for (size_t i = 1; i <= p->io->procnum; i++) {
       if (i != p->self_id)
           while(receive((void*)p, i, &msg) != 0);
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
    sync_state(&p, STARTED, payload, len);

    fprintf(io->events_log_stream, log_received_all_started_fmt, id);
    /* Work. */
    /* Process's done. */
    len = sprintf(payload, log_done_fmt, id);
    fputs(payload, io->events_log_stream); 
    /* Process syncs wih ohers. */
    sync_state(&p, DONE, payload, len);
    fprintf(io->events_log_stream, log_received_all_done_fmt, id);
    return 0;
}
