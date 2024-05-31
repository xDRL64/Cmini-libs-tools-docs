#include <stdio.h>
#include <string.h>
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


// USING :

int main(int argc, char *argv[]){

    // Check mode, display version (app name only || app name + -v|--v|-version|--version)
    if (printVersion(argc, argv)){
        // Stop app
        return 0;
    }

    return 0;
}

