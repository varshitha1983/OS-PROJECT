
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Declare the ispaused system call
extern int ispaused(void);

int main() {
    printf("Running pause-resume demo. Press Ctrl+C to toggle pause/resume.\n");

    while (1) {
        if (ispaused()) {
            // Process is paused
            printf("Paused. Press Ctrl+C to resume.\n");

            // Wait until the process is resumed
            while (ispaused()) {
                sleep(1);  // Avoid excessive CPU usage
            }
        } else {
            // Process is running
            printf("Running...\n");
            sleep(1);  // Control the output rate
        }
    }

    exit(0);
}

