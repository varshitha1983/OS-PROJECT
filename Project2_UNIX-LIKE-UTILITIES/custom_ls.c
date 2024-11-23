#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *path, int show_all, int show_sizes) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) {
        perror("custom_ls");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!show_all && entry->d_name[0] == '.')
            continue;

        if (show_sizes) {
            struct stat file_stat;
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
            if (stat(filepath, &file_stat) == 0) {
                printf("%-20s %10ld bytes\n", entry->d_name, file_stat.st_size);
            }
        } else {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    int show_all = 0, show_sizes = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) show_all = 1;
        else if (strcmp(argv[i], "-s") == 0) show_sizes = 1;
    }

    list_files(".", show_all, show_sizes);
    return 0;
}
