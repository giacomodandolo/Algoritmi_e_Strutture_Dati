#include "ST.h"

typedef struct st_t {
    char *list;
    int N, maxN;
} *ST;

ST STinit(int maxN) {
    ST x;

    x = (ST) malloc(sizeof(*x));
    x->list = (char*) malloc(maxN*sizeof(char));
    x->N = 0;
    x->maxN = maxN;

    return x;
}

void STfree(ST st) {
    free(st->list);
    free(st);
}

void STinsert(ST st, char c) {
    if (STsearch(st, c) != -1)
        return;

    st->list[st->N] = c;
    st->N = st->N + 1;
}

char STsearchByIndex(ST st, int i) {
    return st->list[i];
}

int STsearch(ST st, Key k) {
    int i;

    for (i = 0; i < st->N; i++)
        if (k == st->list[i])
            return i;

    return -1;
}
