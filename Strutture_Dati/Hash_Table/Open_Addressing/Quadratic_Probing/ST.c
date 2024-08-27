#include "ST.h"

#define c1 1
#define c2 1

void STinsert(ST st, Item item) {
    int i = 0, start = hash(KEYget(&item), st->M), index = start;

    while (full(st, index)) {
        i++;
        index = (start + c1*i + c2*i*i)%st->M;
    }
    st->a[index] = item;
    st->N++;
}

Item STsearch(ST st, Key k) {
    int i = 0, start = hash(k, st->M), index = start;

    while (full(st, index))
        if (KEYcmp(k, KEYget(&st->a[index])) == 0)
            return st->a[index];
        else {
            i++;
            index = (start + c1*i + c2*i*i)%st->M;
        }
    
    return ITEMsetNull();
}

void STdelete(ST st, Key k) {
    int i=0, start = hash(k, st->M), index = start;
    Item tmp;

    while (full(st, index))
        if (KEYcmp(k, KEYget(&st->a[index])) == 0) 
            break;
        else { 
            i++;  
            index = (start + c1*i + c2*i*i)%st->M;
        }
    if (ITEMcheckNull(st->a[index])) 
        return;
    st->a[index] = ITEMsetNull();
    st->N--; 
    i++;
    index = (start + c1*i + c2*i*i)%st->M;
    while(full(st, index)) {
        tmp = st->a[index];
        st->a[index] = ITEMsetNull();
        st->N--; i++;
        STinsert(st, tmp);
        index = (start + c1*i + c2*i*i)%st->M;
    }
}

