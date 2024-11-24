#include "kernel/types.h"
#include "user/user.h"

// Define NULL if not already defined
#ifndef NULL
#define NULL ((void*)0)
#endif

int main(int argc, char *argv[]) {
  int n;

  if (argc != 2) {
    printf("Usage: testforkmul <number_of_children>\n");
    exit(1);
  }

  n = atoi(argv[1]);
  if (n <= 0) {
    printf("Please provide a positive number of children.\n");
    exit(1);
  }

  int pid = fork_multiple(n);

  if (pid == 0) {
    // Child process
    printf("Child process with PID: %d\n", getpid());
    exit(0);
  } else if (pid > 0) {
    // Parent process
    printf("Parent process with PID: %d created %d child(ren)\n", getpid(), n);
    while (wait(NULL) > 0); // Wait for all child processes to finish
  } else {
    // Fork multiple failed
    printf("Fork multiple failed\n");
    exit(1);
  }

  exit(0);
}
