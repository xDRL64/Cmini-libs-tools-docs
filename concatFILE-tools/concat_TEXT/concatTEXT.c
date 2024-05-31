#include <stdio.h>
#include <regex.h>

#define VERSION "0.0.0a"

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

int main(int argc, char *argv[]) {
    FILE *outputFile;
    FILE *inputFile;
    char buffer[1024];
    size_t bytesRead;

    // Check mode, display version (app name only || app name + -v|--v|-version|--version)
    if (printVersion(argc, argv)){
        // Stop app
        return 0;
    }

    // Check there are at least 3 args (app name + ouput name + names of files to concat)
    if (argc < 3) {
        printf("Using: %s <output_file> <input_file1> <input_file2> ... <input_fileN>\n", argv[0]);
        return 1;
    }

    // Open output file in write mode
    outputFile = fopen(argv[1], "w");
    if (outputFile == NULL) {
        perror("Error by opening output file");
        return 1;
    }

    // Concat input files within the output file
    for (int i = 2; i < argc; i++) {
        inputFile = fopen(argv[i], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "Error by opening input file: %s\n", argv[i]);
            fclose(outputFile);
            return 1;
        }

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
            fwrite(buffer, 1, bytesRead, outputFile);
        }

        fprintf(outputFile, "\n");

        if (ferror(inputFile)) {
            fprintf(stderr, "Error reading input file: %s\n", argv[i]);
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        fclose(inputFile);
    }

    // Close output file
    fclose(outputFile);

    printf("Concat process : Done.\n");

    return 0;
}
