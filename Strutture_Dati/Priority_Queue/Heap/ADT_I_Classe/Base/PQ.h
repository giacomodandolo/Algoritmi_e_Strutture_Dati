#ifndef PQ_H
#define PQ_H

typedef struct pqueue *PQ;

/* INIZIALIZZAZIONE */
PQ PQinit(int maxN);
void PQfree(PQ pq);

/* OPERAZIONI DI DIMENSIONE */
int PQempty(PQ pq);
int PQsize(PQ pq);

/* 
    --- INSERIMENTO ---

    Inserisce l'elemento come una foglia, poi controlla se la  
    chiave è maggiore di quella del genitore, e in caso positivo
    si scambiano, e si ripete potenzialmente fino alla radice.
*/
void PQinsert(PQ pq, Item val);

/* 
    --- ESTRAZIONE ---

    Si scambia la radice con l'ultimo elemento dell'heap e
    si estrae, riapplicando successivamente HEAPify.
*/
Item PQextractMax(PQ pq);

/* VISUALIZZAZIONE */
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);

/* 
    --- CAMBIO DI PRIORITA' ---

    Si ricerca l'elemento da inserire nella coda.
    Se è presente, si applica l'operazione di inserimento.
*/
void PQchange(PQ pq, Item val);

#endif