#include "Ora.h"

Ora *ORAload(int hh, int mm) {
    Ora *x;

    x = (Ora*) malloc(sizeof(Ora));
    x->hh = hh;
    x->mm = mm;

    return x;
}

void ORAstore(FILE* file, Ora *o) {
    fprintf(file, "%d:%d", o->hh, o->mm);
}