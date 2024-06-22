#include <stdio.h>
#include <string.h>

#define VERSION "0.0.0a"

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("printMSG Version : %s\n", VERSION);
        printf("Usage : %s <message> <?color1> <?color2>\n", argv[0]);
        printf("color arg syntax : r|R|_r|_R | red|Red|_red|_Red\n");
        printf("color type arg :\n");
        printf("\tnormal fg :: r|red\n");
        printf("\tbright fg :: R|Red\n");
        printf("\tnormal bg :: _r|_red\n");
        printf("\tbright bg :: _R|_Red\n");
        printf("color arg available :\n");
        printf("\t(_)[k|K]black\n");
        printf("\t(_)[r|R]ed\n");
        printf("\t(_)[g|G]reen\n");
        printf("\t(_)[y|Y]ellow\n");
        printf("\t(_)[b|B]lue\n");
        printf("\t(_)[m|M]agenta\n");
        printf("\t(_)[c|C]yan\n");
        printf("\t(_)[w|W]hite\n");
        printf("\t(Only '_' char and 1st letter do matter)\n");
        return 1;
    }

    char* message = argv[1];

    char* c1 = (argc>2 && argv[2] != NULL) ? argv[2] : "";
    char* c2 = (argc>3 && argv[3] != NULL) ? argv[3] : "";

    char* col[] = {c1, c2};

    int color = 39; // default
    int bgcol = 109; // default

    int t = 0, v = 0;
    int* _color = &color;

    for(int i=0; i<2; i++){

        if (col[i][0] == '_') {
            t = 1; v = 10;
            _color = &bgcol;
        } else {
            t = 0; v = 0;
            _color = &color;
        }

        // nornal
        if (col[i][t] == 'k') *_color = 30+v; // black
        if (col[i][t] == 'r') *_color = 31+v; // red
        if (col[i][t] == 'g') *_color = 32+v; // green
        if (col[i][t] == 'y') *_color = 33+v; // yellow
        if (col[i][t] == 'b') *_color = 34+v; // blue
        if (col[i][t] == 'm') *_color = 35+v; // magenta
        if (col[i][t] == 'c') *_color = 36+v; // cyan
        if (col[i][t] == 'w') *_color = 37+v; // white

        // bright
        if (col[i][t] == 'K') *_color = 90+v; // black
        if (col[i][t] == 'R') *_color = 91+v; // red
        if (col[i][t] == 'G') *_color = 92+v; // green
        if (col[i][t] == 'Y') *_color = 93+v; // yellow
        if (col[i][t] == 'B') *_color = 94+v; // blue
        if (col[i][t] == 'M') *_color = 95+v; // magenta
        if (col[i][t] == 'C') *_color = 96+v; // cyan
        if (col[i][t] == 'W') *_color = 97+v; // white
    }

    printf("\033[1;%d;%dm%s\033[0m", color, bgcol, message);

    return 0;
}
