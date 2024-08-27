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
    int i = st->size++;

    if (st->size > st->maxN) {
        st->a = realloc(st->a, (2*st->maxN)*sizeof(Item));
        if (st->a == NULL) 
            return;
        st->maxN = 2*st->maxN;
        }
    while((i > 0) && KEYcmp(KEYget(&val), KEYget(&st->a[i-1])) == -1) {
        st->a[i] = st->a[i-1];
        i--;
    }
    st->a[i] = val;
}

static Item searchR(ST st, int l, int r, Key k) {
    int m;

    m = (l + r)/2;
    if (l > r) 
        return ITEMsetvoid();
    if (KEYcmp(k, KEYget(&st->a[m])) == 0) 
        return st->a[m];
    if (l == r) 
        return ITEMsetvoid();
    if (KEYcmp(k, KEYget(&st->a[m])) == -1)
        return searchR(st, l, m-1, k);
    else
        return searchR(st, m+1, r, k);
}

Item STsearch(ST st, Key k) {
    return searchR(st, 0, st->size-1, k) ;
}

Item STselect(ST st, int r) { 
    return st->a[r]; 
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
