#ifndef ST_H
#define ST_H

typedef struct symboltable *ST;

/* INIZIALIZZAZIONE */
ST  STinit(int maxN, float r);

/* OPERAZIONI DI DIMENSIONE */
int full(ST st, Item item);

/* INSERIMENTO */
void STinsert(ST st, Item val);

/* RICERCA */
Item STsearch(ST st, Key k);

/* CANCELLAZIONE */
void STdelete(ST st, Key k);

#endif