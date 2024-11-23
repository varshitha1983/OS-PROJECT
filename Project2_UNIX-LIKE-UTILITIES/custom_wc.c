#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void count_file(const char *filename, int count_lines, int count_words, int count_chars) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("custom_wc");
        return;
    }

    int lines = 0, words = 0, chars = 0;
    char ch, prev_ch = '\0';

    while ((ch = fgetc(file)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        if (isspace(ch) && !isspace(prev_ch)) words++;
        prev_ch = ch;
    }

    if (count_lines) printf("Lines: %d\n", lines);
    if (count_words) printf("Words: %d\n", words);
    if (count_chars) printf("Characters: %d\n", chars);

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-l|-w|-c] <filename>\n", argv[0]);
        return 1;
    }

    int count_lines = 0, count_words = 0, count_chars = 0;
    const char *filename = argv[argc - 1];

    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-l") == 0) count_lines = 1;
        else if (strcmp(argv[i], "-w") == 0) count_words = 1;
        else if (strcmp(argv[i], "-c") == 0) count_chars = 1;
    }

    if (!count_lines && !count_words && !count_chars) {
        count_lines = count_words = count_chars = 1;
    }

    count_file(filename, count_lines, count_words, count_chars);
    return 0;
}
