#include "ST.h"

typedef struct STnode *link;
struct STnode {
    Item val;
    link next;
};
typedef struct {
    link head;
    int size;
} list;
struct symbtab {
    list tab;
};

static link NEW(Item val, link next) {
    link x = malloc(sizeof(*x));

    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;

    return x;
}

ST STinit(int maxN) {
    ST st;
    
    st = malloc(sizeof(*st));
    if(st == NULL) 
        return NULL;
    st->tab.size = 0;
    st->tab.head = NULL;
    
    return st;
}

void STfree(ST st) {
    link x, t;

    for (x = st->tab.head; x != NULL; x = t) {
        t = x->next;
        free(x);
    }
    free(st);
}

int STcount(ST st) {
    return st->tab.size;
}

void STinsert(ST st, Item val) {
    if (st == NULL)
        return;
    st->tab.head = NEW(val, st->tab.head);
    st->tab.size++;
}

Item STsearch(ST st, Key k) {
    link x;

    if (st == NULL)
        return ITEMsetvoid();
    if (st->tab.head == NULL)
       return ITEMsetvoid();
    for (x = st->tab.head; x != NULL; x = x->next)
        if (KEYcmp( KEYget(&x->val), k) ==0)
            return x->val;
    
    return ITEMsetvoid();
}

void STdelete(ST st, Key k) {
    link x, p;

    if (st == NULL) 
        return;
    if (st->tab.head == NULL) 
        return;
    for (x = st->tab.head, p = NULL; x != NULL; p = x, x = x->next) {
        if (KEYcmp(k, KEYget(&x->val)) == 0) {
            if (x == st->tab.head)
                st->tab.head = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    st->tab.size--;
}

void STdisplay(ST st) {
    link x;

    for (x = st->tab.head; x != NULL; x = x->next)
        ITEMstore(x->val);
}
