#include "ST.h"

typedef struct st_t {
    Item **list;
    int N, maxN;
} *ST;

ST STinit(int maxN) {
    int i;
    ST st;

    st = (ST) malloc(sizeof(*st));
    st->list = (Item**) malloc(maxN * sizeof(Item*));
    for (i = 0; i < maxN; i++)
        st->list[i] = ITEMsetvoid();
    st->maxN = maxN;
    st->N = 0;

    return st;
}

void STfree(ST st) {
    int i;

    for (i = 0; i < st->maxN; i++)
        free(st->list[i]);
    free(st->list);
    free(st);
}

int STcount(ST st) {
    return st->N;
}

void STinsert(ST st, Item* item) {
    int i, N;
    //Key k, tmp;

    N = STcount(st);
    //k = KEYget(item);

    if (N > st->maxN) {
        st->list = realloc(st->list, (2*st->maxN)*sizeof(Item*));
        if (st->list == NULL)
            return;
        st->maxN = 2*st->maxN;
    }

    /*for (i = N; i > 0; i--) {
        tmp = KEYget(st->list[i-1]);
        if (KEYcmp(tmp, k) > 0)
            st->list[i] = st->list[i-1];
        else
            break;
    }*/

    st->list[N] = item;
    st->N = st->N + 1;
}

/*int STsearch(ST st, Key k) {
    int i, j, m, pos;

    i = 0, j = STcount(st), pos = -1;
    do {
        m = (i+j)/2;
        if (KEYcmp(KEYget(st->list[m]), k) == 0)
            pos = m;
        else if (KEYcmp(KEYget(st->list[m]), k) > 0)
            j = m - 1;
        else
            i = m + 1;
    } while (i <= j && pos == -1);
    
    return pos;
}*/

int STsearch(ST st, Key k) {
    int i;

    for (i = 0; i < st->N; i++) {
        if (KEYcmp(KEYget(st->list[i]), k) == 0)
            return i;
    }
    
    return -1;
}

void STdisplayByIndex(ST st, int i) {
    ITEMstore(st->list[i]);
}

Item *STsearchByIndex(ST st, int i) {
    if (KEYcmp(KEYget(st->list[i]), "") == 0)
        return NULL;
    return st->list[i];
}