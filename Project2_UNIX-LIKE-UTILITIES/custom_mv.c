#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void move_file(const char *source, const char *destination, int verbose) {
    if (rename(source, destination) == 0) {
        if (verbose) {
            printf("Moved %s to %s successfully.\n", source, destination);
        }
    } else {
        perror("custom_mv");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-v] <source> <destination>\n", argv[0]);
        return 1;
    }

    int verbose = 0;
    const char *source = argv[argc - 2];
    const char *destination = argv[argc - 1];

    for (int i = 1; i < argc - 2; i++) {
        if (strcmp(argv[i], "-v") == 0) verbose = 1;
    }

    move_file(source, destination, verbose);
    return 0;
}
