#include "PQ.h"

typedef struct PQnode *link;
struct PQnode{ 
    Item val; 
    link next; 
};
struct pqueue { 
    link head; 
};

link NEW(Item val, link next) {
    link x = malloc(sizeof(*x));
    
    x->val = val; 
    x->next = next;
    
    return x;
}

PQ PQinit(int maxN) {
    PQ pq = malloc(sizeof(*pq)) ;

    pq->head = NULL;
    
    return pq;
}

int PQempty(PQ pq) {
    return pq->head == NULL;
}

void PQinsert(PQ pq, Item val) {
    link x, p;
    Key k = KEYget(val);

    if (pq->head == NULL || KEYless(KEYget(pq->head->val), k)) {
        pq->head = NEW(val, pq->head);
        return;
    }
    for (x = pq->head->next, p = pq->head; x != NULL && KEYless(k, KEYget(x->val)); p = x, x = x->next);
    p->next = NEW(val, x);
    
    return;
}

Item PQextractMax(PQ pq) {
    Item tmp;
    link t;

    if (PQempty(pq)) {
        printf("PQ empty\n");
        return ITEMsetvoid();
    }
    tmp = pq->head->val;
    t = pq->head->next;
    free(pq->head);
    pq->head = t;

    return tmp;
}

Item PQshowMax(PQ pq) {
    return pq->head->val;
}

void PQdisplay(PQ pq) {
    link x;

    for (x = pq->head; x != NULL; x = x->next)
        ITEMdisplay(x->val);
    
    return;
}

void PQchange(PQ pq, Item val) {
    link x, p;

    if (PQempty(pq)) {
        printf("PQ empty\n"); 
        return;
    }
    for(x = pq->head, p = NULL; x != NULL; p = x, x = x->next) {
        if (ITEMeq(x->val, val)) {
            if (x == pq->head) 
                pq->head = x->next;
            else 
                p->next = x->next;
            free(x);
            break;
        }
    }
    PQinsert(pq, val);

    return;
}