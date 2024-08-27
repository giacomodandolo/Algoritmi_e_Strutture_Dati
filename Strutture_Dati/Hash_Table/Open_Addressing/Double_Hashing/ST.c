#include "ST.h"

static int hash1(Key k, int M) {
    int h = 0, base = 127;
    
    for ( ; *k != '\0'; k++) 
        h = (base * h + *k) % M;
    
    return h;
}

static int hash2(Key k, int M) {
    int h = 0, base = 127;

    for ( ; *k != '\0'; k++) 
        h = (base * h + *k);
    h = ((h % 97) + 1)%M;
    if (h == 0) 
        h = 1;
    
    return h;
}

void STinsert(ST st, Item item) {
    int i = hash1(KEYget(&item), st->M);
    int j = hash2(KEYget(&item), st->M);

    while (full(st, i))
        i = (i+j)%st->M;
    st->a[i] = item;
    st->N++;
}

Item STsearch(ST st, Key k) {
    int i = hash1(k, st->M);
    int j = hash2(k, st->M);

    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i])) == 0)
            return st->a[i];
        else
            i = (i+j)%st->M;

    return ITEMsetNull();
}

void STdelete(ST st, Key k) {
    int i = hash1(k, st->M), j = hash2(k); 
    Item tmp;
    
    while (full(st, i))
        if (KEYcmp(k, KEYget(&st->a[i])) == 0) 
            break;
        else 
            i = (i+j) % st->M;
    if (ITEMcheckNull(st->a[i]))
        return;
    st->a[i] = ITEMsetNull();
    st->N--;
    i = (i+j) % st->M;
    while(full(st, i)) {
        tmp = st->a[i];
        st->a[i] = ITEMsetNull();
        st->N--;
        STinsert(st, tmp);
        i = (i+j) % st->M;
    }
}
