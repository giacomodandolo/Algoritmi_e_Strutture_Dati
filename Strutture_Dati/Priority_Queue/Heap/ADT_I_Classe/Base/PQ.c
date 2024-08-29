#include "PQ.h"

struct pqueue { 
    Item *A; 
    int heapsize; 
};

static int LEFT(int i) { 
    return (i*2 + 1); 
}

static int RIGHT(int i) { 
    return (i*2 + 2); 
}

static int PARENT(int i) { 
    return ((i-1)/2); 
}

PQ PQinit(int maxN) {
    PQ pq = malloc(sizeof(*pq));
    pq->A = (Item*) malloc(maxN*sizeof(Item));
    pq->heapsize = 0;
    return pq;
}

void PQfree(PQ pq) {
    free(pq->A);
    free(pq);
}

int PQempty(PQ pq) { 
    return pq->heapsize == 0; 
}

int PQsize(PQ pq) { 
    return pq->heapsize; 
}

void PQinsert(PQ pq, Item val) {
    int i;

    i = pq->heapsize++;
    while((i >= 1) && (KEYcmp(KEYget(pq->A[PARENT(i)]), KEYget(val)) == -1)) {
        pq->A[i] = pq->A[PARENT(i)];
        i = (i-1)/2;
    }
    pq->A[i] = val;
    
    return;
}

Item PQextractMax(PQ pq) {
    Item val;
    
    Swap(pq, 0, pq->heapsize-1);
    val = pq->A[pq->heapsize-1];
    pq->heapsize--;
    HEAPify(pq, 0);
    
    return val;
}

Item PQshowMax(PQ pq) { 
    return pq->A[0]; 
}

void PQdisplay(PQ pq) {
    int i;
    for (i = 0; i < pq->heapsize; i++)
        ITEMstore(pq->A[i]);
}

void PQchange(PQ pq, Item val) {
    int i, found = 0, pos;

    for (i = 0; i < pq->heapsize && found == 0; i++)
        if (NAMEcmp(NAMEget(&(pq->A[i])), NAMEget(&val)) == 0) {
            found = 1;
            pos = i;
        }
    if (found == 1) {
        while(pos >= 1 && PRIOget(pq->A[PARENT(pos)]) < PRIOget(val)) {
            pq->A[pos] = pq->A[PARENT(pos)];
            pos = (pos-1)/2;
        }
        pq->A[pos] = val;
        Heapify(pq, pos);
    } else
        printf("key not found!\n");
    
    return;
}
