#include "Titolo.h"

typedef struct titolo_t {
    char codice[MAX_LEN];
    int qMax, qMin;
    BST q;
} Titolo;

Titolo *TITOLOinit(char *codice) {
    Titolo *x;

    x = (Titolo*) malloc(sizeof(Titolo));
    strcpy(x->codice, codice);
    x->qMax = INT_MIN;
    x->qMin = INT_MAX;
    x->q = BSTinit();

    return x;
}

Titolo *TITOLOsetvoid() {
    Titolo *x;

    x = (Titolo*) malloc(sizeof(Titolo));
    strcpy(x->codice, "");
    x->qMax = INT_MIN;
    x->qMin = INT_MAX;
    x->q = BSTinit();

    return x;
}

void TITOLOstore(FILE* file, Titolo *t) {
    fprintf(file, "%s\n", t->codice);
    TITOLOstoreMaxMin(file, t);
    BSTstore(file, t->q);
}

int TITOLOgetQuot(Titolo *t) {
    return BSTvisitInOrderQuot(t->q);
}

void TITOLOstoreMaxMin(FILE* file, Titolo *t) {
    fprintf(file, "qMax = %d\nqMin = %d\n", t->qMax, t->qMin);
}

void TITOLOstoreQuotDate(FILE *file, Titolo *t, Data *d1, Data *d2) {
    int min = INT_MAX, max = INT_MIN;

    BSTvisitInOrderQuotDate(t->q, d1, d2, &min, &max);
    fprintf(file, "qMax = %d\nqMin = %d\n", max, min);
}

Titolo *TITOLOaddQuot(Titolo *t, Quot *qu) {
    Quot *q;

    q = QUOTload(qu->data, qu->ora, qu->val, qu->num);
    BSTinsertLeaf(t->q, q);
    BSTgetMinMax(t->q, QUOTgetKey(qu), &(t->qMin), &(t->qMax));

    return t;
}

KeyT TITOLOgetKey(Titolo *t) {
    return t->codice;
}

int TITOLOcmpKey(KeyT k1, KeyT k2) {
    return strcmp(k1, k2);
}