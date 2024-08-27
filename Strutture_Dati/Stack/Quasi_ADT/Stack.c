#include "Stack.h"

typedef struct STACKnode *link;
struct STACKnode {
    Item val;
    link next;
};
static link head;

static link NEW(Item val, link next) {
    link x = (link) malloc(sizeof(*x));

    x->val = val;
    x->next = next;

    return x;
}

void STACKinit(int maxN) {
    head = NULL;
}

int STACKempty() {
    return head == NULL;
}

void STACKpush(Item val) {
    head = NEW(val, head);
}

Item STACKpop() {
    Item tmp = head->val;
    link t = head->next;

    free(head);
    head = t;
    
    return tmp;
}