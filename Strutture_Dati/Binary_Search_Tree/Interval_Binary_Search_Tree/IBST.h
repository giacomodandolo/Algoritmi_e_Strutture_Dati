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

/* RICERCA */
Item IBSTsearch(IBST ibst, Item x);

/* VISITA */
void IBSTvisit(IBST ibst, int strategy);

#endif