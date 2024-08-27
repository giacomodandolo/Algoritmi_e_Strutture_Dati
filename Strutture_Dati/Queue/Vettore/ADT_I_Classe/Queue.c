#include "Queue.h"

struct queue {
    Item *q;
    int N, head, tail;
};

QUEUE QUEUEinit(int maxN) {
    QUEUE q = malloc(sizeof *q);

    q->q = malloc(maxN*sizeof(Item));
    q->N = maxN+1;
    q->head = q->N;
    q->tail = 0;

    return q;
}

int QUEUEempty(QUEUE q) {
    return (q->head)%(q->N) == q->tail;
}

void QUEUEput(QUEUE q, Item val) {
    q->q[tail++] = val;
    q->tail = (q->tail)%(q->N);
}

Item QUEUEget(QUEUE q) {
    q->head = (q->head)%(q->N);

    return q->q[q->head++];
}