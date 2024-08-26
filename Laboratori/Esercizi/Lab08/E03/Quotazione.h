#ifndef QUOTAZIONE_H
#define QUOTAZIONE_H
#include "Data.h"
#include "Ora.h"

typedef struct quot_t {
    Data *data;
    Ora *ora;
    int val, num, tot;
} Quot;
typedef Data KeyQ;

Quot *QUOTsetvoid();
Quot *QUOTload(Data *data, Ora *ora, int val, int num);
void QUOTstore(FILE* file, Quot *q);
KeyQ *QUOTgetKey(Quot *q);
int QUOTgetTot(Quot *q);
int QUOTcmpKey(KeyQ *k1, KeyQ *k2);

#endif