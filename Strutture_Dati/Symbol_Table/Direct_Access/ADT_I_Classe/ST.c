#include "ST.h"

struct symbtab {
    Item *a;
    int N, M;
}

/* LETTERE MAIUSCOLE ALFABETO */
int GETindex(Key k) {
    int i;,

    i = k - 'A';

    return i;
}

/* INTERI TRA 0 E M-1 */
int GETindex(Key k) {
    int i;

    i = (int) k;

    return i;
}

/* STRINGHE DI LUNGHEZZA FISSA E CORTA */
int GETindex(Key k) {
    int i = 0, b = 26;
    
    for ( ; *k != '\0'; k++)
        i = (b * i + (*k - ((int) 'A')));

    return i;
}

ST STinit(int maxN) {
    ST st;
    int i;

    st = malloc(sizeof(*st));
    st->a = malloc(maxN*sizeof(Item));
    for (i = 0; i < maxN; i++)
        st->a[i] = ITEMsetvoid();
    st->M = maxN;
    st->N= 0;

    return st;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

int STcount(ST st) {
    return st->N;
}

void STinsert(ST st, Item val) {
    int index = GETindex(KEYget(val));

    st->a[index] = val;
    st->N++;
}

Item STsearch(ST st, Key k) {
    int index = GETindex(k);

    return st->a[index];
}

Item STselect(ST st, int r) {
    int i;

    for (i = 0; i < st->M; i++)
        if ((ITEMcheckvoid(st->a[i])==0) && (r-- == 0))
            return st->a[i];
    
    return NULL;
}

void STdelete(ST st, Key k) {
    st->a[GETindex(k)] = ITEMsetvoid();
    st->N--;
}

void STdisplay(ST st){
    int i;

    for (i = 0; i < st->M; i++)
        if (ITEMcheckvoid(st->a[i]) == 0) 
            ITEMstore(st->a[i]);
}
