#define _GNU_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "ipc.h"
#include "pa1.h"
#include "child.h"

/** Get attributes of the process from the command line.
 * 
 * @param argc      Argument count.
 * @param argv      Argument vector.
 * @param procnum   Total count of the child processes. 
 */
static inline size_t
get_options(int argc, char *argv[]) {
    size_t procnum = -1;
    switch(getopt(argc, argv, "p:")) {
        case 'p': {
            char *endptr = NULL;
            procnum = strtol(optarg, &endptr, 10);   
            if (optarg == endptr || procnum > MAX_PROC || procnum <= 0) {
                return 0;
            }
            break;
        }
        default:
            return 0;
    }
    return procnum;
}

/** Creates pipes for IPC.
 * 
 * @param io    I/O description.
 */
static int
create_pipes(IO *io) {
    int count = 1;
    for (int i = 0; i <= io->procnum; i++) {
        for (int j = 0; j <= io->procnum; j++) {
            if (i == j) {
                io->fds[i][j][0] = -1;
                io->fds[i][j][1] = -1;
                continue;
            }
            fprintf(io->pipes_log_stream, "Created pipe number %d.\n", count++);

            if (pipe2(io->fds[i][j], O_DIRECT) < 0) {
               perror("pipe");
               return -1;
            }
        }
    }
    return 0;
}

static void
wait_msg(proc_t *p) {
    Message msg = { {0} };
    for (size_t i = 1; i <= p->io->procnum; i++) {
        while(receive((void*)p, i, &msg) != 0);
    }
}

static void
wait_all(IO *io) {
    proc_t p = (proc_t) {
        .io = io,
        .self_id = 0
    };

    wait_msg(&p);
    fprintf(io->events_log_stream, log_received_all_started_fmt, PARENT_ID);

    wait_msg(&p);
    fprintf(io->events_log_stream, log_received_all_done_fmt, PARENT_ID);
    while(wait(NULL) > 0);
}

int
main(int argc, char *argv[]) {
    IO io = {0};

    if ((io.procnum = get_options(argc, argv)) == 0)
        return -1;

    io.events_log_stream = fopen(events_log, "w+");
    if (io.events_log_stream == NULL) {
        perror("fopen");
        return -1;
    }

    io.pipes_log_stream = fopen(pipes_log, "w");
    if (io.pipes_log_stream == NULL) {
        perror("fopen");
        return -1;
    }

    if (create_pipes(&io) < 0)
        return -1;

    for (int i = 1; i <= io.procnum; i++) {
        pid_t pid = fork();
        if (0 > pid) {
            exit(EXIT_FAILURE);
        } else if (0 == pid) {
            /* Child. */
            int ret = child(&io, i);
            exit(ret);
        }
    }
    close_unsed_fds(&io, PARENT_ID);
    wait_all(&io);
    fclose(io.pipes_log_stream);
    fclose(io.events_log_stream);
    return 0;
}
