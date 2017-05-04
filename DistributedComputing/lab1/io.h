#ifndef __IFMO_DISTRIBUTED_CLASS_IO__H
#define __IFMO_DISTRIBUTED_CLASS_IO__H

#include <stdio.h>

#define MAX_PROC    10
#define MAX_PIPES   110
#define NUM_FD      2

#define READ_FD     0
#define WRITE_FD    1

#define INDEX(from_id, to_id, pnum) \
    (from_id*pnum + (to_id > from_id ? to_id - 1 : to_id))

typedef struct {
    size_t procnum;
    size_t pipesnum;
   
    FILE *events_log_stream;
    FILE *pipes_log_stream;

    int fds[MAX_PIPES][MAX_PROC];
} __attribute__((packed)) IO;

#endif /* __IFMO_DISTRIBUTED_CLASS_IO__H */
