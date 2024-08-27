#include "Queue.h"

typedef struct QUEUEnode *link;
struct QUEUEnode { 
    Item val; 
    link next; 
};
struct queue { 
    link head; 
    link tail; 
};

link NEW(Item val, link next) {
    link x = malloc(sizeof(*x));

    x->val = val; 
    x->next = next;
    
    return x;
}

QUEUE QUEUEinit(int maxN) {
    QUEUE q = malloc(sizeof(*q));

    q->head = NULL;

    return q;
}

int QUEUEempty(QUEUE q) {
    return q->head == NULL;
}

void QUEUEput (QUEUE q, Item val) {
    if (q->head == NULL) {
        q->tail = NEW(val, q->head) ;
        q->head = q->tail;
        return;
    }
    q->tail->next = NEW(val,q->tail->next);
    q->tail = q->tail->next;
}

Item QUEUEget(QUEUE q) {
    Item tmp = q->head->tmp;
    link t = q->head->next;
    
    free(q->head); 
    q->head = t;
    
    return tmp;
}