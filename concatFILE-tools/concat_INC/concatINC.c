#include <stdio.h>
#include <string.h>
#include <regex.h>

#define VERSION "0.0.0a"
#define DEFAULT_MARKER_REGEXP "(\\s*)(;//CONCAT_HERE)"

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
    FILE *outputFile = NULL;
    FILE *templateFile = NULL;
    FILE *markerFile = NULL;
    FILE *inputFile = NULL;
    char buffer[1024];
    size_t bytesRead;
    char line[1024];
    regex_t regex;
    regmatch_t matches[2];
    int indentationLength = 0;
    int foundMarker = 0;
    char markerRegex[1024];


    /* 
    // Check mode, display version (app name only || app name + -v|--v|-version|--version)
    printf("argv[0] : %s\n", argv[0]);
    printf("argv[1] : %s\n", argv[1]);
    
    // argv[1] === abc-vABC
    if (argc <= 2) {
        if (regcomp(&regex, "^(--version|-version|--v|-v)$", REG_EXTENDED) != 0) {
            fprintf(stderr, "Error compiling regular expression 1st\n");
            return 1;
        }
        if (regexec(&regex, argv[1], 2, matches, 0) == 0) {

            printRegGrp(argv[1], &matches[0]); // full sample match
            printRegGrp(argv[1], &matches[1]); // group match
        }else
             printf("no a ver flag\n");

        regfree(&regex); // Free the regular expression
        return 0;
    } */

    // Check mode, display version (app name only || app name + -v|--v|-version|--version)
    if (printVersion(argc, argv)){
        // Stop app
        return 0;
    }

    // Check there are at least 4 args (app name + output name + template name + names of files to concat)
    if (argc < 4) {
        printf("Using: %s <output_file> <template_file> <input_file1> <input_file2> ... <input_fileN>\n", argv[0]);
        return 1;
    }

    // Open output file in write mode
    outputFile = fopen(argv[1], "w");
    if (outputFile == NULL) {
        perror("Error by opening output file");
        return 1;
    }

    // Open template file in read mode
    templateFile = fopen(argv[2], "r");
    if (templateFile == NULL) {
        perror("Error by opening template file");
        fclose(outputFile);
        return 1;
    }

    // Open marker file in read mode
    markerFile = fopen("./marker.regexp.txt", "r");
    if (markerFile == NULL) {
        printf("Warning './marker.regexp.txt' not found. Default regepx's marker is :\n%s\n", DEFAULT_MARKER_REGEXP);
        // Use default regexp's marker
        strcpy(markerRegex, DEFAULT_MARKER_REGEXP);
        
    } else {
        // Read the marker regular expression from the file
        if (fgets(markerRegex, sizeof(markerRegex), markerFile) == NULL) {
            fprintf(stderr, "Error reading marker regular expression from file\n");
            fclose(markerFile);
            fclose(outputFile);
            fclose(templateFile);
            return 1;
        }

        // Remove the newline character from the end of the marker regular expression
        // (based on the first encountered '\n')
        markerRegex[strcspn(markerRegex, "\n")] = '\0';

        fclose(markerFile);
    }

    // Compile the regular expression to find the marker and its indentation
    if (regcomp(&regex, markerRegex, REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regular expression\n");
        fclose(outputFile);
        fclose(templateFile);
        return 1;
    }

    // Copy template content to output file until the marker is found
    while (fgets(line, sizeof(line), templateFile) != NULL) {
        if (regexec(&regex, line, 2, matches, 0) == 0) {
            indentationLength = matches[1].rm_eo - matches[1].rm_so;
            foundMarker = 1;
            break;
        }
        fprintf(outputFile, "%s", line);
    }

    regfree(&regex); // Free the regular expression

    if (!foundMarker) {
        fprintf(stderr, "Marker not found in template file\n");
        fclose(outputFile);
        fclose(templateFile);
        return 1;
    }

    // Concat input files within the output file
    for (int i = 3; i < argc; i++) {
        inputFile = fopen(argv[i], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "Error by opening input file: %s\n", argv[i]);
            fclose(outputFile);
            fclose(templateFile);
            return 1;
        }

        while (fgets(line, sizeof(line), inputFile) != NULL) {
            fprintf(outputFile, "%*s%s", indentationLength, "", line);
        }

        fprintf(outputFile, "\n");

        if (ferror(inputFile)) {
            fprintf(stderr, "Error reading input file: %s\n", argv[i]);
            fclose(inputFile);
            fclose(outputFile);
            fclose(templateFile);
            return 1;
        }

        fclose(inputFile);
    }

    // Copy the rest of the template content to output file
    while (fgets(line, sizeof(line), templateFile) != NULL) {
        fprintf(outputFile, "%s", line);
    }

    if (ferror(templateFile)) {
        fprintf(stderr, "Error reading template file\n");
        fclose(outputFile);
        fclose(templateFile);
        return 1;
    }

    // Close files
    fclose(templateFile);
    fclose(outputFile);

    printf("Concat process : Done.\n");

    return 0;
}