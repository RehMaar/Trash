#ifndef __IFMO_DISTRIBUTED_CLASS_PA1_CHILD_H__
#define __IFMO_DISTRIBUTED_CLASS_PA1_CHILD_H__

#include <stdio.h>
#include "ipc.h"
#include "io.h"

typedef struct {
    const IO *io;
    local_id self_id;
} proc_t;

int child(IO *io, local_id id);

#endif /* __IFMO_DISTRIBUTED_CLASS_PA1_CHILD_H__ */
