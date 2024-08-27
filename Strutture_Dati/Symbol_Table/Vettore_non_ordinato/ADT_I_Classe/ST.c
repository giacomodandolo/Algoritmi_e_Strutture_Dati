#include "ST.h"

struct symbtab {
    Item *a; 
    int maxN; 
    int size;
};

ST STinit(int maxN) {
    ST st; 
    int i;
    
    st = malloc(sizeof(*st));
    st->a = malloc(maxN * sizeof(Item));
    for (i = 0; i < maxN; i++)
        st->a[i] = ITEMsetvoid();
    st->maxN = maxN;
    st->size = 0;

    return st;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

int STcount(ST st) {
    return st->size; 
}

void STinsert(ST st, Item val) {
    int i = st->size;

    if (st->size >= st->maxN) {
        st->a=realloc(st->a,(2*st->maxN)*sizeof(Item));
        if (st->a == NULL) return;
            st->maxN = 2*st->maxN;
    }
    st->a[i] = val; st->size++;
}

Item STsearch(ST st, Key k) {
    int i;

    if (st->size == 0) 
        return ITEMsetvoid();
    for (i = 0; i < st->size; i++)
        if (KEYcmp(k, KEYget(&st->a[i])) == 0) 
            return st->a[i];
    
    return ITEMsetvoid();
}

void STdelete(ST st, Key k) {
    int i, j = 0;

    while (KEYcmp(KEYget(&st->a[j]), k) != 0)
        j++;
    for (i = j; i < st->size-1; i++)
        st->a[i] = st->a[i+1];
    st->size--;
}

void STdisplay(ST st){
    int i;

    for (i = 0; i < st->size; i++)
        ITEMstore(st->a[i]);
}
