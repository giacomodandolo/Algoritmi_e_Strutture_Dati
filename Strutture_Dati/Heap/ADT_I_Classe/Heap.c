#include "Heap.h"

struct heap {
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

Heap HEAPinit(int maxN) {
    Heap h;

    h = malloc(sizeof(*h));
    h->A = malloc(maxN*sizeof(Item));
    h->heapsize = 0;

    return h;
}

void HEAPfree(Heap h) {
    free(h->A);
    free(h);
}

void HEAPfill(Heap h, Item item) {
    int i;

    i = h->heapsize++;
    h->A[i] = item;

    return;
}

void HEAPsort(Heap h) {
    int i, j;

    HEAPbuild(h);
    j = h->heapsize;
    for (i = h->heapsize-1; i > 0; i--) {
        Swap (h, 0, i);
        h->heapsize--;
        HEAPify(h, 0);
    }
    h->heapsize = j;
}

void HEAPdisplay(Heap h) {
    int i;
    
    for (i = 0; i < h->heapsize; i++)
        ITEMstore(h->A[i]);
}

void HEAPify(Heap h, int i) {
    int l, r, largest;

    l = LEFT(i);
    r = RIGHT(i);
    if ((l < h->heapsize) && KEYcmp(KEYget(h->A[l]), KEYget(h->A[i])) == 1)
        largest = l;
    else
        largest = i;
    if ((r < h->heapsize) && KEYcmp(KEYget(h->A[r]), KEYget(h->A[largest])) == 1)
        largest = r;
    if (largest != i) {
        Swap(h, i, largest);
        HEAPify(h, largest);
    }
}

void HEAPbuild(Heap h) {
    int i;

    for (i = (h->heapsize)/2 - 1; i >= 0; i--)
        HEAPify(h, i);
}