#ifndef BST_H
#define BST_H

typedef struct binarysearchtree *BST;

/* INIZIALIZZAZIONE */
BST BSTinit();
void BSTfree(BST bst);

/* OPERAZIONI DI DIMENSIONE */
int BSTcount(BST bst);
int BSTempty(BST bst);

/* INSERIMENTO */
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);

/* CANCELLAZIONE */
void BSTdelete(BST bst, Key k);

/* RICERCA */
Item BSTsearch(BST bst, Key k);

/* SELEZIONE */
Item BSTselect(BST bst, int r);

/* MIN/MAX */
Item BSTmin(BST bst); 
Item BSTmax(BST bst);

/* VISITA */
void BSTvisit(BST bst, int strategy);

/* SUCCESSIVO/PRECEDENTE */
Item BSTsucc(BST bst, Key k);
Item BSTpred(BST bst, Key k);

/* ROTAZIONE */
link rotL(link h);
link rotR(link h);

/* PARTIZIONAMENTO */
link partR(link h, int r);

/* CONNESSIONE ALBERI */
link joinLR(link a, link b, link z);

/* BILANCIAMENTO */
void BSTbalance(BST bst);

#endif