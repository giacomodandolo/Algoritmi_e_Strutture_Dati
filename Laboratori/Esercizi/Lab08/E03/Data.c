#include "Data.h"

Data *DATAload(int y, int m, int d) {
    Data *x;

    x = (Data*) malloc(sizeof(Data));
    x->y = y;
    x->m = m;
    x->d = d;

    return x;
}

void DATAstore(FILE* file, Data *d) {
    fprintf(file, "%d/%d/%d", d->y, d->m, d->d);
}

int DATAcmp(Data *d1, Data *d2) {
    if (d1->y == d2->y) {
        if (d1->m == d2->m)
            return d1->d - d2->d;
        return d1->m - d2->m;
    }

    return d1->y - d2->y;
}