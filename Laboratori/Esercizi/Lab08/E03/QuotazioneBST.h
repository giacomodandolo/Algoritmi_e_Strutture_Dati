#ifndef QUOTAZIONEBST_H
#define QUOTAZIONEBST_H
#include "Quotazione.h"

typedef struct nodeBST_t nodeBST, *linkBST;
typedef struct bst_t *BST;

BST BSTinit();
void BSTinsertLeaf(BST bst, Quot *item);
void BSTstore(FILE *file, BST bst);
Quot *BSTsearch(BST bst, KeyQ *k);
void BSTgetMinMax(BST bst, KeyQ *k, int *min, int *max);
int BSTvisitInOrderQuot(BST bst);
void BSTvisitInOrderQuotDate(BST bst, Data *d1, Data *d2, int *min, int *max);
/*
Quot *BSTmax(BST bst);
Quot *BSTmin(BST bst);
*/

#endif