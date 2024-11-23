#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to display the contents of a single file with optional transformations
void display_file(const char *filename, int to_upper, int to_lower) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "custom_cat: Could not open file '%s'\n", filename);
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        // Apply transformations
        if (to_upper) {
            fputc(toupper(ch), output_stream);
        } else if (to_lower) {
            fputc(tolower(ch), output_stream);
        } else {
            fputc(ch, output_stream);
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-u|-l] <filename1> [<filename2> ...]\n", argv[0]);
        return 1;
    }

    int to_upper = 0, to_lower = 0;
    int start_idx = 1; // Default start index for filenames

    // Parse optional flags (-u or -l)
    if(strcmp(argv[1],"-u") == 0){
	to_upper = 1;
	start_idx = 2;
    }else if(strcmp(argv[1],"-l") == 0){
	to_lower = 1;
	start_idx = 2;
    }

    if (start_idx >= argc) {
        fprintf(stderr, "custom_cat: No files specified\n");
        return 1;
    }

    // Concatenate and process each file
    for (int i = start_idx; i < argc; i++) {
        display_file(argv[i], to_upper, to_lower); // Output file content to stdout

        // Add a newline between files (optional but standard in concatenation)
        if (i < argc - 1) {
            putchar('\n');
        }
    }

    return 0;
}

