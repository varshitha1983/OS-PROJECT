#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a line contains a pattern (with optional case insensitivity)
int contains(const char *line, const char *pattern, int case_insensitive) {
    char line_copy[1024], pattern_copy[256];
    strcpy(line_copy, line);
    strcpy(pattern_copy, pattern);

    // Convert both line and pattern to lowercase if case_insensitive is enabled
    if (case_insensitive) {
        for (int i = 0; line_copy[i]; i++) line_copy[i] = tolower(line_copy[i]);
        for (int i = 0; pattern_copy[i]; i++) pattern_copy[i] = tolower(pattern_copy[i]);
    }

    return strstr(line_copy, pattern_copy) != NULL; // Return true if pattern is found
}

// Function to search for a pattern in a file and handle options
void search_file(const char *filename, const char *pattern, int case_insensitive, int invert_match) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("custom_grep"); // Error if the file can't be opened
        return;
    }

    char line[1024];
    int found_flag = 0; // Flag to indicate if a match was found

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        int matched = contains(line, pattern, case_insensitive);
        // Print the line if it matches (or doesn't match, based on invert_match)
        if(invert_match){
		if(!matched){
			printf("%s",line);
		}
	}
	else if (matched) {
            printf("%s", line);
            found_flag = 1;
        }
    }

    if (!found_flag) {
        printf("Not found\n");
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-i|-v] <pattern> <filename>\n", argv[0]);
        return 1;
    }

    int case_insensitive = 0, invert_match = 0;
    const char *pattern = argv[argc - 2];
    const char *filename = argv[argc - 1];

    // Parse command-line options
    for (int i = 1; i < argc - 2; i++) {
        if (strcmp(argv[i], "-i") == 0) case_insensitive = 1;
        else if (strcmp(argv[i], "-v") == 0) invert_match = 1;
    }

    // Call the search function
    search_file(filename, pattern, case_insensitive, invert_match);

    return 0;
}
