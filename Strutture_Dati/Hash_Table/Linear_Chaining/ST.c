#include "ST.h"

typedef struct STnode* link;
struct STnode { 
    Item item; 
    link next; 
};
struct symbtab { 
    link *heads; 
    int N, M;
    link z; 
};

static link NEW( Item item, link next) {
    link x = malloc(sizeof(*x));

    x->item = item; 
    x->next = next;

    return x;
}

ST STinit(int maxN, float r) {
    int i;
    ST st;

    st = malloc(sizeof(*st));
    st->N = 0;
    st->M = STsizeSet(maxN, r);
    st->heads = malloc(st->M*sizeof(link));
    st->z = NEW(ITEMsetNull(), NULL);
    for (i=0; i < st->M; i++)
        st->heads[i] = st->z;
    
    return st;
}

void STfree(ST st) {
    int i;
    link t,u;

    for(i = 0; i < st->M; i++)
        for (t = st->heads[i]; t != st->z; t = u) {
            u = t->next;
            free(t);
        }
    free(st->z);
    free(st->heads);
    free(st);
}

int STcount(ST st) {
    return st->N;
}

int STempty(ST st) {
    if (STcount(st) == 0)
        return 1;
    return 0;
}

static int hash(Key v, int M) {
    int h = 0, base = 127;

    for ( ; *v != '\0'; v++) 
    h = (base * h + *v) % M;

    return h;
}

static int hashU(Key v, int M) {
    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;

    return h;
}

void STinsert(ST st, Item val) {
    int i;

    i = hash(KEYget(&val), st->M);
    st->heads[i] = NEW(val, st->heads[i]);
}

static Item searchR(link t, Key k, link z) {
    if (t == z) 
        return ITEMsetNull();
    if ((KEYcmp(KEYget(&t->item), k)) == 0) 
        return t->item;
    return searchR(t->next, k, z);
}

Item STsearch(ST st, Key k) {
    return searchR(st->heads[hash(k, st->M)], k, st->z);
}

static link deleteR(link x, Key k) {
    if (x == NULL) 
        return NULL;
    if ((KEYcmp(KEYget(&x->item), k)) == 0) {
        link t = x->next; 
        free(x); 
        return t;
    }
    x->next = deleteR(x->next, k);
    
    return x;
}

void STdelete(ST st, Key k) {
    int i = hash(k, st->M);

    st->heads[i] = deleteR(st->heads[i], k);
}

static void visitR(link h, link z) {
    if (h == z) 
        return;
    ITEMstore(h->item);
    visitR(h->next, z);
}

void STdisplay(ST st)  {
    int i;

    for (i = 0; i < st->M; i++) {
        printf("st->heads[%d] = ", i);
        visitR(st->heads[i], st->z);
        printf("\n");
    }
}


