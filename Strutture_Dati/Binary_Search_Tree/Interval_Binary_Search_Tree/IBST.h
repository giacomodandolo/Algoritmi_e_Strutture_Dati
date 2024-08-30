#ifndef IBST_H
#define IBST_H
#include "Item.h"

typedef struct intervalbinarysearchtree *IBST;

/* INIZIALIZZAZIONE */
void IBSTinit(IBST ibst);
void IBSTfree(IBST ibst);

/* OPERAZIONI DI DIMENSIONI */
int IBSTcount(IBST ibst);
int IBSTempty(IBST ibst);

/* INSERIMENTO */
void BSTinsert(IBST ibst, Item x);

/* ROTAZIONE */
link rotL(link h);
link rotR(link h);

/* PARTIZIONE */
link partR(link h, int r);

/* CONNESSIONE ALBERI */
link joinLR(link a, link b, link z);

/* CANCELLAZIONE */
void IBSTdelete(IBST ibst, Item x);

/* 
    --- RICERCA ---

    Si ha la ricerca di un nodo h con intervallo che interseca
    l'intervallo i attraverso il percorrimento dell'albero dalla
    radice e terminando quando viene trovato l'intervallo che
    interseca i oppure si è giunti ad un albero vuoto.
    Si ha ricorsione dal nodo h sul sottoalbero sinistro se
    h->l->max > low[i], altrimenti sul sottoalbero destro. 
*/
Item IBSTsearch(IBST ibst, Item x);

/* VISITA */
void IBSTvisit(IBST ibst, int strategy);

#endif