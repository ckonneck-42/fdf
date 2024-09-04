#include <stdio.h>
#include <stdlib.h>

void multiply_by_100(const char *input_file, const char *output_file) {
    FILE *in_fp = fopen(input_file, "r");
    FILE *out_fp = fopen(output_file, "w");

    if (in_fp == NULL || out_fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int value;
    char line[1024]; // Buffer to store each line

    while (fgets(line, sizeof(line), in_fp)) {
        // Process the line to multiply each number by 100
        char *ptr = line;
        while (sscanf(ptr, "%d", &value) == 1) {
            fprintf(out_fp, "%d ", value * 10);
            // Move the pointer to the next number
            while (*ptr != ' ' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == ' ') {
                ptr++;
            }
        }
        fprintf(out_fp, "\n"); // Newline at the end of each processed line
    }

    fclose(in_fp);
    fclose(out_fp);
}

int main() {
    const char *input_file = "mars.fdf";
    const char *output_file = "mars2.fdf";

    multiply_by_100(input_file, output_file);

    printf("Processing completed. Check '%s' for results.\n", output_file);

    return 0;
}