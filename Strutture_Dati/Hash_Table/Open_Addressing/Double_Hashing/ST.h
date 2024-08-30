#ifndef ST_H
#define ST_H

/* 
    --- DOUBLE HASHING ---
*/

typedef struct symboltable *ST;

/* 
    --- INSERIMENTO --- 

    L'inserimento avviene calcolando i = h1(k). Se la posizione
    è libera si inserisce la chiave, altrimenti si calcola j = h2(k)
    e prova i = (i+j)%M. Si ripete fino a cella vuota. Se M = 2max,
    si ha alpha < 1. Bisogna che il nuovo valore sia diverso dal
    vecchio valore di i.
*/
void STinsert(ST st, Item item);

/* RICERCA */
Item STsearch(ST st, Key k);

/* CANCELLAZIONE */
void STdelete(ST st, Key k);

#endif