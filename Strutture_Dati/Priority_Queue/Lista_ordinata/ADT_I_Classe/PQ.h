#ifndef PQ_H
#define PQ_H

typedef struct pqueue *PQ;

/* INIZIALIZZAZIONE */
PQ PQinit(int maxN);

/* OPERAZIONI DI DIMENSIONE */
int PQempty(PQ pq);

/* INSERIMENTO */
void PQinsert(PQ pq, Item data);

/* ESTRAZIONE */
Item PQextractMax(PQ pq);

/* VISUALIZZAZIONE */
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);

/* CAMBIO DI PRIORITA' */
void PQchange(PQ pq, Item data);

#endif