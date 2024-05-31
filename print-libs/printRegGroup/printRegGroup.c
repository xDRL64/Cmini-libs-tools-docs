#include <stdio.h>
#include <string.h>
#include <regex.h>

void printRegGrp(char* sample, regmatch_t* group){
    int gSize = group->rm_eo - group->rm_so;
    char str[gSize + 1];
    strncpy(str, sample+group->rm_so, gSize);
    str[gSize] = 0;
    printf("s: %d\n", group->rm_so);
    printf("e: %d\n", group->rm_eo);
    printf("%s\n", str);
}

int main(int argc, char *argv[]){
    regex_t regex;
    regmatch_t matches[2];
        
    if (regcomp(&regex, "abc(xyz)$", REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regular expression\n");
        return 1;
    }

    char sample[] = "123abcxyz";

    if (regexec(&regex, sample, 2, matches, 0) == 0) {

        printRegGrp(sample, &matches[0]); // full sample match
        printRegGrp(sample, &matches[1]); // 1st group match
        
        return 1;
    }

    regfree(&regex); // Free the regular expression

    return 0;
}
