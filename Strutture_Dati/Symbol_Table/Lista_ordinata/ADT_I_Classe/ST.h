#ifndef ST_H
#define ST_H

typedef struct symboltable *ST;

/* INIZIALIZZAZIONE */
ST STinit(int maxN);
void STfree(ST st);

/* OPERAZIONI DI DIMENSIONE */
int STcount(ST st);

/* INSERIMENTO */
void STinsert(ST st, Item val);

/* RICERCA */
Item STsearch(ST st, Key k);

/* SELEZIONE */
Item STselect(ST st, int r);

/* CANCELLAZIONE */
void STdelete(ST st, Key k);

/* VISUALIZZAZIONE */
void STdisplay(ST st);

#endif