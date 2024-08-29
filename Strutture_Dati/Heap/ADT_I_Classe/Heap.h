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

/* 
    --- TRASFORMAZIONE IN HEAP ---

    Questa trasformazione richiede che il valore sinistro e
    quello destro siano già heap.

    Se l'elemento sinistro è maggiore del padre, allora
    l'indice dell'elemento sinistro è il più alto, altrimenti
    il padre rimane il massimo. Se l'elemento destro è maggiore
    del precedente massimo, allora l'indice dell'elemento destro
    è il più alto. In caso il più largo non sia il padre, allora 
    l'albero è già un heap, altrimenti si scambiano il padre e il
    massimo e si applica la trasformazione all'elemento scambiato.
*/
void HEAPify(Heap h, int i);

/* 
    --- COSTRUZIONE DELL'HEAP ---

    Partendo dai padri delle foglie, si applica HEAPify fino alla radice. 
*/
void HEAPbuild(Heap h);

#endif