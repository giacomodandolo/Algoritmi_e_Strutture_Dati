#ifndef ORA_H
#define ORA_H
#include "General.h"

typedef struct ora_t {
    int hh, mm;
} Ora;

Ora *ORAload(int hh, int mm);
void ORAstore(FILE* file, Ora *o);

#endif