#include "ST.h"

struct symboltable { 
    Item *a; 
    int N, M;
};

ST STinit(int maxN, float alpha) {
    int i;
    ST st = malloc(sizeof(*st));

    st->N = 0;
    st->M = STsizeSet(maxN, alpha);
    if (st->M == -1)
        st = NULL;
    else {
        st->a = malloc(st->M * sizeof(Item));
        for (i = 0; i < st->M; i++)
            st->a[i] = ITEMsetNull();
    }
    return st;
}

void STinsert(ST st, Item item) {
    int i = hash(KEYget(&item), st->M);

    while (full(st, i))
        i = (i+1)%st->M;
    st->a[i] = item;
    st->N++;
}

int full(ST st, int i) {
    if (ITEMcheckNull(st->a[i])) 
        return 0;
    return 1;
}

Item STsearch(ST st, Key k) {
    int i = hash(k, st->M);

    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i])) == 0)
            return st->a[i];
        else
            i = (i+1)%st->M;

    return ITEMsetNull();
}

void STdelete(ST st, Key k) {
    int j, i = hash(k, st->M);
    Item tmp;

    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i])) == 0)
            break;
        else
            i = (i+1) % st->M;
    if (ITEMcheckNull(st->a[i]))
        return;
    st->a[i] = ITEMsetNull();
    st->N--;
    for (j = i+1; full(st, j); j = (j+1)%st->M, st->N--) {
        tmp = st->a[j];
        st->a[j] = ITEMsetNull();
        STinsert(st, tmp);
    }
}


