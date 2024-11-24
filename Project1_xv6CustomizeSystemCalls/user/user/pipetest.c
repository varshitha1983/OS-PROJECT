// priority_pipes_test.c
#include "kernel/types.h"
#include "user/user.h"
int main() {
  int fds[2];
  char buf[512];

  // Create a pipe
  if (pipe(fds) < 0) {
    printf("Error creating pipe\n");
    exit();
  }

  // Write messages with different priorities
  priority_pipes(fds[1], "Low priority message", 20, 3);
  priority_pipes(fds[1], "High priority message", 22, 1);
  priority_pipes(fds[1], "Medium priority message", 24, 2);

  // Read messages in priority order
  for (int i = 0; i < 3; i++) {
    read(fds[0], buf, sizeof(buf));
    printf("Read: %s\n", buf);
  }

  close(fds[0]);
  close(fds[1]);
  exit();
}
