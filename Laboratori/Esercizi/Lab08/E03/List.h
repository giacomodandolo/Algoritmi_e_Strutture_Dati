#ifndef COLLTITOLO_H
#define COLLTITOLO_H
#include "Titolo.h"

typedef struct nodeCT_t nodeCT, *linkCT;
typedef struct collTitolo_t *List;

List LISTinit();
Titolo *LISTsetvoid(List list);
void LISTstore(FILE* file, List l, KeyT codice);
void LISTstoreQuot(FILE* file, List l, KeyT codice);
void LISTstoreQuotDate(FILE *file, List l, KeyT k, KeyQ *d1, KeyQ *d2);
void LISTstoreMaxMin(FILE *file, List l, KeyT k);
List LISTinsOrd(List l, Titolo *item);
Titolo *LISTsearch(List l, KeyT k);
List LISTupdate(List l, KeyT codice, Quot *q);

#endif