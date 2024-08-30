#ifndef ST_H
#define ST_H

/* 
    --- LINEAR CHAINING ---

    Con il linear chaining più elementi possono risiedere nella
    stessa locazione della tabella attraverso una lista concatenata.
    Le operazioni specifiche sono l'inserimento in testa alla lista,
    ricerca dalla lista e cancellazione dalla lista.
*/

typedef struct symboltable *ST;

/* INIZIALIZZAZIONE */
ST STinit(int maxN, float r);
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