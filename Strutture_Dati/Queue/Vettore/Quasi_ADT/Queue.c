#include "Queue.h"

static Item *q;
static int N, head, tail;

void QUEUEinit(int maxN) {
    q = malloc((maxN+1)*sizeof(Item));
    N = maxN + 1;
    head = N;
    tail = 0;
}

int QUEUEempty() {
    return head%N == tail;
}

void QUEUEput(Item val) {
    q[tail++] = val;
    tail = tail%N;
}

Item QUEUEget() {
    head = head%N;
    return q[head++];
}