#ifndef DATA_H
#define DATA_H
#include "General.h"

typedef struct data_t {
    int y, m, d;
} Data;

Data *DATAload(int y, int m, int d);
void DATAstore(FILE* file, Data *d);
int DATAcmp(Data *d1, Data *d2);

#endif