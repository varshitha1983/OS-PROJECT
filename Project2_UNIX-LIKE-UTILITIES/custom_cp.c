#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    if (!src) {
        perror("custom_cp");
        return;
    }
    FILE *dest = fopen(destination, "wb");
    if (!dest) {
        perror("custom_cp");
        fclose(src);
        return;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    fclose(src);
    fclose(dest);
}

void copy_directory(const char *source, const char *destination) {
    DIR *dir = opendir(source);
    if (!dir) {
        perror("custom_cp");
        return;
    }

    // Create destination directory if it doesn't exist
    if (mkdir(destination, 0755) && errno != EEXIST) {
        perror("custom_cp");
        closedir(dir);
        return;
    }

    struct dirent *entry;
    char src_path[1024], dest_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(src_path, sizeof(src_path), "%s/%s", source, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", destination, entry->d_name);

        struct stat entry_stat;
        if (stat(src_path, &entry_stat) == -1) {
            perror("custom_cp");
            continue;
        }

        if (S_ISDIR(entry_stat.st_mode)) {
            // Recursively copy subdirectories
            copy_directory(src_path, dest_path);
        } else {
            // Copy files
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-r] <source> <destination>\n", argv[0]);
        return 1;
    }

    int recursive = 0;
    const char *source, *destination;

    if (strcmp(argv[1], "-r") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s [-r] <source> <destination>\n", argv[0]);
            return 1;
        }
        recursive = 1;
        source = argv[2];
        destination = argv[3];
    } else {
        source = argv[1];
        destination = argv[2];
    }

    struct stat source_stat;
    if (stat(source, &source_stat) == -1) {
        perror("custom_cp");
        return 1;
    }

    if (S_ISDIR(source_stat.st_mode)) {
        if (!recursive) {
            fprintf(stderr, "custom_cp: omitting directory '%s'\n", source);
            return 1;
        }
        copy_directory(source, destination);
    } else {
        copy_file(source, destination);
    }

    return 0;
}

