#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define VERSION "0.0.0a"

#define DEFAULT_MAX_LINE_LENGTH 1024
#define MIN_LINE_LENGTH 1024

int printVersion(int argc, char *argv[]){
    regex_t regex;

    if (argc == 2) {
        if (regcomp(&regex, "^(--version|-version|--v|-v)$", REG_EXTENDED) != 0) {
            fprintf(stderr, "Error compiling regular expression\n");
            return 1;
        }

        if (regexec(&regex, argv[1], 0, NULL, 0) == 0) {
            printf("Version : %s\n", VERSION);
            return 1;
        }

        regfree(&regex); // Free the regular expression
    }

    return 0;
}

void regsub(regmatch_t match, const char *replacement, const char *input, char *output);

int main(int argc, char *argv[]) {

    char *regex_pattern;
    char *replacement_string;
    char *output_name;
    char *input_name;

    char *line_buffer;
    char *newline_buffer;
    int line_size = DEFAULT_MAX_LINE_LENGTH;

    regex_t regex;
    regmatch_t match;

    FILE *output_file;
    FILE *input_file;

    // Check mode, display version (app name only || app name + -v|--v|-version|--version)
    if (printVersion(argc, argv)){
        // Stop app
        return 0;
    }

    if (argc < 5) {
        printf("Using: %s <output_name> <input_name> <regex_pattern> <replacement_string> <line_buffer_size>\n", argv[0]);
        return 1;
    }

    output_name = argv[1];
    input_name = argv[2];
    regex_pattern = argv[3];
    replacement_string = argv[4];

    // optional arg : line buffer size
    if(argc > 5) line_size = atoi(argv[5]);
    if(line_size < MIN_LINE_LENGTH) line_size = MIN_LINE_LENGTH;

    line_buffer = malloc(line_size);
    newline_buffer = malloc(line_size+strlen(replacement_string));

    // Open output file in write mode
    output_file = fopen(output_name, "w");
    if (output_file == NULL) {
        perror("Error by opening output file");
        free(line_buffer);
        free(newline_buffer);
        return 1;
    }

    // Open input file in read mode
    input_file = fopen(input_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        free(line_buffer);
        free(newline_buffer);
        fclose(output_file);
        return 1;
    }

    // Compile the regular expression
    if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regular expression\n");
        free(line_buffer);
        free(newline_buffer);
        fclose(output_file);
        fclose(input_file);
        return 1;
    }

    // replace process
    int line_count = 0, unchanged = 0, replaced = 0; // end process stats
    while (fgets(line_buffer, line_size, input_file) != NULL) {
        if (regexec(&regex, line_buffer, 1, &match, 0) == 0) {
            regsub(match, replacement_string, line_buffer, newline_buffer);
            fprintf(output_file, "%s", newline_buffer);
            replaced++;
        } else {
            fprintf(output_file, "%s", line_buffer);
            unchanged++;
        }
        line_count++;
    }

    printf("Replacement Process done :\n");
    printf("Line buffer size : %d, Found lines : %d\n", line_size, line_count);
    printf("Unchanged lines : %d, Replaced occurences : %d\n", unchanged, replaced);

    // free mem
    //

    free(line_buffer);
    free(newline_buffer);

    regfree(&regex);

    if (fclose(output_file) != 0) {
        printf("Error while output file closing.\n");
        return 1;
    }
    if (fclose(input_file) != 0) {
        printf("Error while input file closing.\n");
        return 1;
    }

    return 0;
}

void regsub(regmatch_t match, const char *replacement, const char *input, char *output) {
    int offset = match.rm_so;
    strncpy(output, input, offset);
    strcpy(output+offset, replacement);
    offset += strlen(replacement);
    strcpy(output+offset, input+match.rm_eo);
    offset += strlen(input+match.rm_eo);
    output[offset] = '\0';
}
