#ifndef __IFMO_DISTRIBUTED_CLASS_PA1_CHILD_H__
#define __IFMO_DISTRIBUTED_CLASS_PA1_CHILD_H__

#include <stdio.h>
#include "ipc.h"
#include "io.h"

typedef struct {
    const IO *io;       /**< Contrainter with I/O metadata. */
    local_id self_id;   /**< ID for the process. */
} proc_t;

/** Child main function.
 * 
 * @param fds   Array of pipes' descriptors.
 * @param id    ID of the child process.
 * @param num   Number of processes.
 */ 
int child(IO *io, local_id id);

/** Close unused file descriptors.
 * 
 * @param fds   Array of pipes' descriptors.
 * @param id    ID of the child process.
 * @param num   Number of processes.
 * 
 */ 
void
close_unsed_fds(IO *io, local_id id);
#endif /* __IFMO_DISTRIBUTED_CLASS_PA1_CHILD_H__ */
