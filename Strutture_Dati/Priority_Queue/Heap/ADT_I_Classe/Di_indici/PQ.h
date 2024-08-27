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
void PQinsert(PQ pq, int index, int prio);

/* ESTRAZIONE */
int PQextractMax(PQ pq);

/* VISUALIZZAZIONE */
int PQshowMax(PQ pq);
void PQdisplay(PQ pq);

/* CAMBIO DI PRIORITA' */
void PQchange(PQ pq, int index, int prio);

#endif