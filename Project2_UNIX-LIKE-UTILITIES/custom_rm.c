#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Function to delete files
void remove_file(const char *path) {
    if (remove(path) != 0) {
        perror("Error deleting file");
    } else {
        printf("Deleted file: %s\n", path);
    }
}

void remove_directory(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("custom_rm");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
		continue;
	}
            struct stat st;
            if (stat(full_path, &st) == 0) {
                if (S_ISDIR(st.st_mode)) {
                    remove_directory(full_path);  // Recursively remove directories
                } else {
                    if (remove(full_path) != 0) {
                        perror("remove file");
                    }
                }
            }
        }
    }

    closedir(dp);

    if (rmdir(path) != 0) {
        perror("rmdir");
    }
}

void custom_rm(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-r] <file_or_directory>\n", argv[0]);
        return;
    }

    int recursive = 0;
    const char *target = NULL;

    // Check if recursive option is specified
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            recursive = 1;
        }
    }

    target = argv[argc - 1];

    struct stat st;
    if (stat(target, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            if (recursive) {
                remove_directory(target);  // Recursively remove directory
            } else {
                fprintf(stderr, "%s: Is a directory. Use '-r' option to remove directories.\n", target);
            }
        } else {
            remove_file(target);
        }
    } else {
        perror("custom_rm");
    }
}

int main(int argc, char *argv[]) {
    custom_rm(argc, argv);
    return 0;
}

