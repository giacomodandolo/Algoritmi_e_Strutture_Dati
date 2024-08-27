#ifndef PQ_H
#define PQ_H

typedef struct pqueue *PQ;

/* INIZIALIZZAZIONE */
PQ PQinit(int maxN);
void PQfree(PQ pq);

/* OPERAZIONI DI DIMENSIONE */
int PQempty(PQ pq);
int PQsize(PQ pq);

/* INSERIMENTO */
void PQinsert(PQ pq, Item val);

/* ESTRAZIONE */
Item PQextractMax(PQ pq);

/* VISUALIZZAZIONE */
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);

/* CAMBIO DI PRIORITA' */
void PQchange(PQ pq, Item val);

#endif