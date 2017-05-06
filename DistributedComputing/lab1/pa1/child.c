#include <malloc.h>
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
    fprintf(io->pipes_log_stream, "ID %d close r/w.\n", id);
    fflush(io->pipes_log_stream);
    for (size_t i = 0; i <= io->procnum; i++) {
        if (i != id) {
            int retw = close(io->fds[INDEX(i,id, io->procnum)].w);
            int retr = close(io->fds[INDEX(id,i, io->procnum)].r);
            fprintf(io->pipes_log_stream, "ID %d closes r(%lu)[%d] w(%lu)[%d]\n",
                    id, INDEX(id,i,io->procnum), retr,
                        INDEX(i,id,io->procnum), retw);
            fflush(io->pipes_log_stream);
        }
    }
    fprintf(io->pipes_log_stream, "ID: %d close unused\n", id);
    fflush(io->pipes_log_stream);
    for (size_t i = 0; i <= io->procnum; i++) {
        for (size_t j = 0; j <= io->procnum; j++) {
            if (i != j && i != id && j != id) {
                int retw = close(io->fds[INDEX(i, j, io->procnum)].w);
                int retr = close(io->fds[INDEX(i, j, io->procnum)].r);
                fprintf(io->pipes_log_stream, "ID %d closes %zu [%d, %d]\n",
                        id, INDEX(i, j, io->procnum), retr, retw);
                fflush(io->pipes_log_stream);
            }
        }
    }
}

/** Syncronization cycle.
 */
static void
sync(proc_t *p, MessageType type, char *payload, size_t payload_len) {
    Message msg = {{ 0 }};
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

    char payload[MAX_PAYLOAD_LEN] = { 0 };
    size_t len;
    proc_t p = (proc_t){
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

    free(io->fds);
    fclose(io->events_log_stream);
    fclose(io->pipes_log_stream);
    
    return 0;
}
