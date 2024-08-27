#ifndef QUEUE_H
#define QUEUE_H

/* INIZIALIZZAZIONE */
void QUEUEinit(int maxN);

/* OPERAZIONI DI DIMENSIONE */
int QUEUEempty();

/* INSERIMENTO */
void QUEUEput(Item val);

/* ESTRAZIONE */
Item QUEUEget();

#endif