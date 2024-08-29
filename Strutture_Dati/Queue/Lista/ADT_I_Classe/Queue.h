#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue *QUEUE;

/* INIZIALIZZAZIONE */
QUEUE QUEUEinit(int maxN);

/* OPERAZIONI DI DIMENSIONE */
int QUEUEempty(QUEUE q);

/* INSERIMENTO */
void QUEUEput(QUEUE q, Item val);

/* ESTRAZIONE */
Item QUEUEget(QUEUE q);

#endif