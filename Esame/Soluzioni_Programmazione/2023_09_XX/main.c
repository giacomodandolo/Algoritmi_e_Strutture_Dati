#include "griglia.h"
#define FILE_GRIGLIA "griglia.txt"
#define FILE_MOSSE "mosse.txt"

int main() {
    Griglia griglia, copy;
    Mosse mosse;
    FILE* file;
    
    file = fopen(FILE_GRIGLIA, "r");
    griglia = griglia_file(file);
    fclose(file);

    file = fopen(FILE_MOSSE, "r");
    mosse = mosse_file(file);
    fclose(file);

    copy = griglia_copy(griglia);
    fprintf(stdout, "EXPECTED = 1\n");
    fprintf(stdout, "RESULT = %d\n", controlla_mosse(&copy, mosse));
    trova_soluzione(griglia, 3);

    return 0;
}