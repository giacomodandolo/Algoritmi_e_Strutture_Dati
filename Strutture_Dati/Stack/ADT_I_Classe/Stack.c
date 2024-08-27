#include "Stack.h"

typedef struct STACKnode *link;
struct STACKnode {
    Item val;
    link next;
};
struct stack {
    link head;
};

static link NEW(Item val, link next) {
    link x = (link) malloc(sizeof(*x));

    x->val = val;
    x->next = next;

    return x;
}

STACK STACKinit(int maxN) {
    STACK s = malloc(sizeof(*s));

    s->head = NULL;

    return s;
}

int STACKempty(STACK s) {
    return s->head == NULL;
}

void STACKpush(STACK s, Item val) {
    s->head = NEW(val, s->head); 
}

Item STACKpop (STACK s) {
    Item tmp = s->head->val;
    link t = s->head->next;

    free(s->head);
    s->head = t;
    
    return tmp;
}