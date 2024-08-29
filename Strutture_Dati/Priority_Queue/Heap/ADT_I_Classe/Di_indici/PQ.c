#include "PQ.h"

typedef struct {
    int index; 
    int prio; 
} heapItem;
struct pqueue {
    heapItem *A; 
    int heapsize; 
    int *qp;
};

PQ PQinit(int maxN) {
    int i; 

    PQ pq = malloc(sizeof(*pq));

    pq->A = malloc(maxN*sizeof(heapItem));
    pq->qp = malloc(maxN*sizeof(int));
    for (i = 0; i < maxN; i++){
        pq->A[i].index = -1; 
        pq->qp[i] = -1; 
    }
    pq->heapsize = 0;

    return pq;
}

void PQfree(PQ pq) {
    free(pq->qp);
    free(pq->A);
    free(pq);
}

int PQempty(PQ pq) { 
    return pq->heapsize == 0; 
}

int PQsize(PQ pq) { 
    return pq->heapsize; 
}

void PQinsert(PQ pq, int index, int prio) {
    int i;

    i = pq->heapsize++;
    while((i >= 1) && (pq->A[PARENT(i)].prio) < prio) {
        pq->A[i] = pq->A[PARENT(i)];
        pq->qp[pq->A[i].index] = i;
        i = PARENT(i);
    }
    pq->A[i].index = index;
    pq->A[i].prio = prio;
    pq->qp[index] = i;
}

static void Swap(PQ pq, int pos1, int pos2) {
    heapItem temp;
    int index1, index2;

    temp = pq->A[pos1];
    pq->A[pos1] = pq->A[pos2];
    pq->A[pos2] = temp;
    index1 = pq->A[pos1].index;
    index2 = pq->A[pos2].index;
    pq->qp[index1] = pos1;
    pq->qp[index2] = pos2;
}

static void HEAPify(PQ pq, int i) {
    int l, r, largest;

    l = LEFT(i);
    r = RIGHT(i);
    if (l < pq->heapsize && (pq->A[l].prio > pq->A[i].prio))
        largest = l;
    else
        largest = i;
    if (r < pq->heapsize && (pq->A[r].prio > pq->A[largest].prio))
        largest = r;
    if (largest != i) {
        Swap(pq, i, largest);
        HEAPify(pq, largest);
    }
}

int PQextractMax(PQ pq) {
    int res;

    Swap(pq, 0, pq->heapsize-1);
    res = pq->A[pq->heapsize-1].index;
    pq->qp[res] = -1;
    pq->heapsize--;
    pq->A[pq->heapsize].index = -1;
    HEAPify(pq, 0);

    return res;
}

void PQchange(PQ pq, int index, int prio) {
    int pos = pq->qp[index];
    heapItem temp = pq->A[pos];
    
    temp.prio = prio;
    while ((pos >= 1) && (pq->A[PARENT(pos)].index < prio)) {
        pq->A[pos] = pq->A[PARENT(pos)];
        pq->qp[pq->A[pos].index] = pos;
        pos = PARENT(pos);
    }
    pq->A[pos] = temp;
    pq->qp[index] = pos;
    HEAPify(pq, pos);
}
