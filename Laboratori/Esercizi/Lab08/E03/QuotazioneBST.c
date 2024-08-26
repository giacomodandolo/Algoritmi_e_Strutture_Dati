#include "QuotazioneBST.h"

typedef struct nodeBST_t {
    Quot *item;
    linkBST l, r;
} nodeBST, *linkBST;

typedef struct bst_t {
    linkBST root, z;
} *BST;

static linkBST NEW(Quot *item, linkBST l, linkBST r) {
    linkBST x;

    x = (linkBST) malloc(sizeof(nodeBST));
    x->item = item;
    x->l = l;
    x->r = r;

    return x;
}

BST BSTinit() {
    BST x;

    x = (BST) malloc(sizeof(*x));
    x->z = NEW(QUOTsetvoid(), NULL, NULL);
    x->root = x->z;

    return x;
}

static linkBST insertLeafR(linkBST h, Quot *item, linkBST z) {
    if (h == z) {
        return NEW(item, z, z);
    }

    if (QUOTcmpKey(QUOTgetKey(item), QUOTgetKey(h->item)) <= 0)
        h->l = insertLeafR(h->l, item, z);
    else 
        h->r = insertLeafR(h->r, item, z);
    
    return h;
}

void BSTinsertLeaf(BST bst, Quot *item) {
    bst->root = insertLeafR(bst->root, item, bst->z);
}

static void storeR(FILE *file, linkBST h, linkBST z) {
    if (h == z)
        return;
    storeR(file, h->l, z);
    QUOTstore(file, h->item);
    storeR(file, h->r, z);
}

void BSTstore(FILE *file, BST bst) {
    storeR(file, bst->root, bst->z);
}

static Quot *searchR(linkBST h, KeyQ *k, linkBST z) {
    if (h == z)
        return QUOTsetvoid();
    
    if (QUOTcmpKey(QUOTgetKey(h->item), k) <= 0)
        return searchR(h->l, k, z);

    return searchR(h->r, k, z);
}

Quot *BSTsearch(BST bst, KeyQ *k) {
    return searchR(bst->root, k, bst->z);
}

static int visitInOrderMax(linkBST h, int *max, KeyQ *k, linkBST z) {
    int tmp;

    if (h == z)
        return INT_MIN;
    
    tmp = visitInOrderMax(h->l, max, k, z);
    if (tmp > *max)
        *max = tmp;

    tmp = QUOTgetTot(h->item);
    if (tmp > *max)
        *max = tmp;

    tmp = visitInOrderMax(h->r, max, k, z);    
    if (tmp > *max)
        *max = tmp;

    return *max;
}

static int visitInOrderMin(linkBST h, int *min, KeyQ *k, linkBST z) {
    int tmp;

    if (h == z)
        return INT_MAX;
    
    tmp = visitInOrderMin(h->l, min, k, z);
    if (tmp < *min)
        *min = tmp;

    tmp = QUOTgetTot(h->item);
    if (tmp < *min)
        *min = tmp;

    tmp = visitInOrderMin(h->r, min, k, z);    
    if (tmp < *min)
        *min = tmp;

    return *min;
}

void BSTgetMinMax(BST bst, KeyQ *k, int *min, int *max) {
    *min = visitInOrderMin(bst->root, min, k, bst->z);
    *max = visitInOrderMax(bst->root, max, k, bst->z);
}

static int visitInOrderQuot(linkBST h, linkBST z, int tot) {
    if (h == z)
        return 0;

    tot = tot + visitInOrderQuot(h->l, z, tot);
    tot = tot + QUOTgetTot(h->item);
    tot = tot + visitInOrderQuot(h->r, z, tot);

    return tot;
}

int BSTvisitInOrderQuot(BST bst) {
    return visitInOrderQuot(bst->root, bst->z, 0);
}

static int visitInOrderMinDate(linkBST h, Data *d1, Data *d2, int *min, linkBST z) {
    int tmp;

    if (h == z)
        return INT_MAX;

    tmp = visitInOrderMinDate(h->l, d1, d2, min, z);
    if (tmp < *min)
        *min = tmp;

    if (DATAcmp(d1, QUOTgetKey(h->item)) <= 0 && DATAcmp(d2, QUOTgetKey(h->item)) >= 0) {
        tmp = QUOTgetTot(h->item);
        if (tmp < *min)
            *min = tmp;
    }

    tmp = visitInOrderMinDate(h->r, d1, d2, min, z);
    if (tmp < *min)
        *min = tmp;

    return *min;
}

static int visitInOrderMaxDate(linkBST h, Data *d1, Data *d2, int *max, linkBST z) {
    int tmp;

    if (h == z)
        return INT_MIN;

    tmp = visitInOrderMaxDate(h->l, d1, d2, max, z);
    if (tmp > *max)
        *max = tmp;

    if (DATAcmp(d1, QUOTgetKey(h->item)) <= 0 && DATAcmp(d2, QUOTgetKey(h->item)) >= 0) {
        tmp = QUOTgetTot(h->item);
        if (tmp > *max)
            *max = tmp;
    }

    tmp = visitInOrderMaxDate(h->r, d1, d2, max, z);
    if (tmp > *max)
        *max = tmp;

    return *max;
}

void BSTvisitInOrderQuotDate(BST bst, Data *d1, Data *d2, int *min, int *max) {
    *min = visitInOrderMinDate(bst->root, d1, d2, min, bst->z);
    *max = visitInOrderMaxDate(bst->root, d1, d2, max, bst->z);
}
