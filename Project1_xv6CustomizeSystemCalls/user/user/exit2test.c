#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child_function(int id) {
    printf("Child process %d running\n", id);
    sleep(10);
    printf("Child process %d exiting\n",id);
    exit(0);
}

int main() {
    int pid1 = fork();
    if (pid1 == 0) {
        child_function(1);
    }

    int pid2 = fork();
    if (pid2 == 0) {
        child_function(2);
    }
    sleep(3);
    printf("Parent process calling exit2\n");
    exit2();  // New system call
    return 0; // This line should never execute
}
