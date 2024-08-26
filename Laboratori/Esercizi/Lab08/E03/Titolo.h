#ifndef TITOLO_H
#define TITOLO_H
#define MAX_LEN 20
#include "QuotazioneBST.h"

typedef struct titolo_t Titolo;
typedef char* KeyT;

Titolo *TITOLOinit(char *codice);
Titolo *TITOLOsetvoid();
void TITOLOstore(FILE* file, Titolo *t);
int TITOLOgetQuot(Titolo *t);
void TITOLOstoreMaxMin(FILE* file, Titolo *t);
void TITOLOstoreQuotDate(FILE *file, Titolo *t, Data *d1, Data *d2);
Titolo *TITOLOaddQuot(Titolo *t, Quot* q);
KeyT TITOLOgetKey(Titolo *t);
int TITOLOcmpKey(KeyT k1, KeyT k2);

#endif