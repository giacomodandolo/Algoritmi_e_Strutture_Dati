#include "Queue.h"

typedef struct QUEUEnode *link;
struct QUEUEnode {
    Item val; 
    link next;
};
static link head, tail;

link NEW (Item val, link next) {
    link x = malloc(sizeof *x);
    
    x->val = val;
    x->next = next;
    
    return x;
}

void QUEUEinit(int maxN) {
    head = tail = NULL;
}

int QUEUEempty() {
    return head == NULL;
}

void QUEUEput(Item val) {
    if (head == NULL) {
        head = (tail = NEW(val, head));
        return;
    }
    tail->next = NEW(val, tail->next);
    tail = tail->next;
}

Item QUEUEget() {
    Item tmp = head->val;
    link t = head->next;
    
    free(head); 
    head = t;
    
    return tmp;
}