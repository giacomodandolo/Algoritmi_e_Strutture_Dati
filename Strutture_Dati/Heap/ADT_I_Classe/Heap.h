#ifndef HEAP_H
#define HEAP_H

typedef struct heap *Heap;

/* INIZIALIZZAZIONE */
Heap HEAPinit(int maxN);
void HEAPfree(Heap h);

/* INSERIMENTO */
void HEAPfill(Heap h, Item val);

/* ORDINAMENTO */
void HEAPsort(Heap h);

/* VISUALIZZAZIONE */
void HEAPdisplay(Heap h);

/* TRASFORMAZIONE IN HEAP */
void HEAPify(Heap h, int i);
void HEAPbuild(Heap h);

#endif