#include "List.h"
#define MAX_FILE 50

void printMenu() {
    printf("0 > Termina il programma;\n");
    printf("1 > Acquisisci transazioni;\n");
    printf("2 > Ricerca un titolo azionario;\n");
    printf("3 > Ricerca la quotazione di un titolo azionario;\n");
    printf("4 > Ricerca la quotazione minima e massima in un intervallo di date;\n");
    printf("5 > Ricerca della quotazione minima e massima totale;\n");
}

List readFile(List LT, char *filename) {
    int i, j, n, k, y, m, d, hh, mm, val, num;
    char codice[MAX_LEN];
    Data *data;
    Ora *ora;
    Quot *q;
    Titolo *t;
    FILE* file;

    file = fopen(filename, "r");
    fscanf(file, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(file, "%s %d", codice, &k);
        for (j = 0; j < k; j++) {
            fscanf(file, "%d/%d/%d %d:%d %d %d", &y, &m, &d, &hh, &mm, &val, &num);
            data = DATAload(y, m, d);
            ora = ORAload(hh, mm);
            q = QUOTload(data, ora, val, num);
            if (LISTsearch(LT, codice) != LISTsetvoid(LT))
                LT = LISTupdate(LT, codice, q);
            else {
                t = TITOLOinit(codice);
                t = TITOLOaddQuot(t, q);
                LT = LISTinsOrd(LT, t);
            }
        }
    }
    fclose(file);
    return LT;
}

int main(void) {
    int scelta, y1, m1, d1, y2, m2, d2;
    char filename[MAX_FILE], codice[MAX_LEN];
    Data *date1, *date2;
    List LT;
    
    LT = LISTinit();
    scelta = -1;
    do {
        printMenu();
        printf("Fai una scelta: ");
        scanf("%d", &scelta);
        printf("\n");

        switch(scelta) {
            case 0:
                break;
            case 1:
                printf("Nome file: ");
                scanf("%s", filename);
                LT = readFile(LT, filename);
                break;
            case 2:
                printf("Titolo azionario: ");
                scanf("%s", codice);
                LISTstore(stdout, LT, codice);
                printf("\n");
                break;
            case 3:
                printf("Titolo azionario: ");
                scanf("%s", codice);
                LISTstoreQuot(stdout, LT, codice);
                printf("\n");
                break;
            case 4:
                printf("Titolo azionario: ");
                scanf("%s", codice);
                printf("Prima data (yyyy/mm/dd): ");
                scanf("%d/%d/%d", &y1, &m1, &d1);
                printf("Seconda data (yyyy/mm/dd): ");
                scanf("%d/%d/%d", &y2, &m2, &d2);
                printf("\n");
                date1 = DATAload(y1, m1, d1);
                date2 = DATAload(y2, m2, d2);
                LISTstoreQuotDate(stdout, LT, codice, date1, date2);
                printf("\n");
                break;
            case 5:
                printf("Titolo azionario: ");
                scanf("%s", codice);
                LISTstoreMaxMin(stdout, LT, codice);
                printf("\n");
                break;
            default:
                printf("Scegli un'operazione valida!");
        }

    } while(scelta != 0);

    return 0;
}