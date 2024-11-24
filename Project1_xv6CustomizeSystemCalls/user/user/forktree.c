
#include "types.h"
#include "stat.h"
#include "user.h"

void test_fork_tree() {
    printf("Testing fork_tree system call...\n");

    // Create 2 children, with grandchildren (2 for child 1, none for child 2)
    fork_tree(2, 2, 0);

    printf("Process tree created successfully.\n");
}

int main(void) {
    test_fork_tree();
    exit();
}
