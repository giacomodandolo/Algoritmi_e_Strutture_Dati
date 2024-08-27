#ifndef ST_H
#define ST_H

typedef struct symboltable *ST;

/* INIZIALIZZAZIONE */
ST  STinit(int maxN, float r);
void STfree(ST st);

/* OPERAZIONI DI DIMENSIONE */
int STcount(ST st);
int STempty(ST st);

/* INSERIMENTO */
void STinsert(ST st, Item val);

/* RICERCA */
Item STsearch(ST st, Key k);

/* CANCELLAZIONE */
void STdelete(ST st, Key k);

/* VISUALIZZAZIONE */
void STdisplay(ST st);

#endif