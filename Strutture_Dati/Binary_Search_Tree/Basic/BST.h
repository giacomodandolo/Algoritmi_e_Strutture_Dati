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

/* RICERCA */
Item BSTsearch(BST bst, Key k);

/* MIN/MAX */
Item BSTmin(BST bst);
Item BSTmax(BST bst);

/* VISITA */
void BSTvisit(BST bst, int strategy);

/* ROTAZIONE */
link rotL(link h);
link rotR(link h);

#endif