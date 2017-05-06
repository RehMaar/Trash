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


/** Eval number of pipes.
 * 
 * @param n  Number of processes.
 * 
 * @algo
 *   Complete graph has E = n(n-1)/2 edges for n nodes.
 *   We need two pipes between two nodes, or E*2, or
 *   E' = n(n - 1).
 */
static inline int
pipes_num(int n) {
    return n*(n - 1);
}

/** Get attributes of the process from the command line.
 * 
 * @param argc      Argument count.
 * @param argv      Argument vector.
 * @param procnum   Total count of the child processes. 
 */
static inline int
get_attributes(int argc, char *argv[], size_t *procnum) {
    switch(getopt(argc, argv, "p:")) {
        case 'p': {
            char *endptr = NULL;
            *procnum = strtol(optarg, &endptr, 10);   
            if (optarg == endptr || *procnum > MAX_PROC || *procnum <= 0) {
                return -1;
            }
            break;
        }
        default:
            return -1;
    }
    return 0;
}

/** Creates pipes for IPC.
 * 
 * @param io    I/O description.
 */
static int
create_pipes(IO *io) {
    io->pipesnum = pipes_num(io->procnum+1);
    for (int i = 0; i < io->pipesnum; i++) {
        fprintf(io->pipes_log_stream, "Created pipe number %d.\n", i+1);
        if (pipe2(io->fds[i], O_NONBLOCK) < 0) {
           perror("pipe");
           return -1;
        }
    }
    return 0;
}

static void
wait_msg(proc_t *p) {
    Message msg = { {0} };
    for (size_t i = 1; i <= p->io->procnum; i++) {
        while(receive((void*)p, i, &msg) != 0);
        fprintf(stderr, "Msg len: %d\n", msg.s_header.s_payload_len);
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
    size_t procnum = 0;

    if (get_attributes(argc, argv, &procnum) < 0)
        return -1;

    for (size_t i = 0; i <= procnum; i++) {
        for (size_t j = 0; j <= procnum; j++) {
            if (i != j)
                fprintf(stderr, "%zu -- %zu : %lu\n", i, j, INDEX(i, j, procnum));
        }
    }

    io.procnum = procnum;
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
    fclose(io.pipes_log_stream);

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
    fclose(io.events_log_stream);
    return 0;
}
