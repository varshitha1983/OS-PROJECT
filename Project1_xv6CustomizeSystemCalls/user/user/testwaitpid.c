#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int pid = fork();  // Create a child process

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }
    if(pid > 0)
    {
        // This is the parent process
        printf("Parent waiting for child PID: %d\n", pid);
        int status;
        int ret = waitpid(pid, &status);  // Wait for the specific child process
        if (ret > 0) {
            printf("Parent: Child %d exited with status %d\n", ret, status);
        } else {
            printf("Parent: waitpid failed\n");
        }
        printf("Statement after child is completed.\n");
    }
    else if (pid == 0) {
        // This is the child process
        sleep(5);
        printf("Child process (PID: %d) running\n", getpid());
        sleep(10);  // Simulate work
        exit(42);   // Exit with status 42
        // sleep(2);  // Simulate work
        // exit(13);   // Exit with status 42
    } 

    exit(0);
}
