

#include "types.h"
#include "spinlock.h"
#define NMSG 64 // Maximum number of messages in the pipe
#define PIPESIZE 512
/*struct priority_msg {
  char data[512];  // Message content
  int priority;    // Message priority (lower value = higher priority)
};*/
struct pipe {
    //char data[512];    // Pipe buffer
    uint nread;        // Number of bytes read
    uint nwrite;       // Number of bytes written
    int readopen;      // Read descriptor is open
    int writeopen;     // Write descriptor is open
    struct spinlock lock; // Lock for synchronizing access
    
  char data[PIPESIZE];
  //struct priority_msg msgs[NMSG];
  int nmsg;        // Number of messages in the pipe 
};

//void pipeclose(struct priority_pipe *pi,int writable);
//int priority_piperead(struct priority_pipe *pi, uint64 addr, int n);
//int priority_pipewrite(struct priority_pipe *pi, uint64 addr, int n,int priority);

