#ifndef PRIORITY_PIPE_H
#define PRIORITY_PIPE_H

#include "param.h"
#include "spinlock.h"

struct priority_pipe {
    struct spinlock lock; // Lock for synchronizing access
    char data[512];       // Data buffer
    int priority[512];    // Priority levels for each byte of data
    int nread;            // Read index
    int nwrite;           // Write index
    int readopen;         // Reader is open
    int writeopen;        // Writer is open
};

#endif
