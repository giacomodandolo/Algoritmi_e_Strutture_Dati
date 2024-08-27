#include "BST.h"

typedef struct BSTnode *link;
struct BSTnode {
    Item item;
    link l;
    link r;
};
struct binarysearchtree {
    link root;
    link z;
};
typedef enum {
    PREORDER, INORDER, POSTORDER
};

static link NEW(Item item, link l, link r) {
    link x = malloc(sizeof *x);

    x->item = item; 
    x->l = l; 
    x->r = r;

    return x;
}

BST BSTinit( ) {
    BST bst = malloc(sizeof *bst);

    bst->root = (bst->z = NEW(ITEMsetNull(), NULL, NULL));

    return bst;
}

void BSTfree(BST bst) {
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

static void treeFree(link h, link z) {
    if (h == z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

static int countR(link h, link z) {
    if (h == z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) +1;
}

int BSTcount(BST bst) {
    return countR(bst->root, bst->z);
}

int BSTempty(BST bst) {
    if (BSTcount(bst) == 0)
        return 1;
    return 0;
}

void BSTinsert_leafI(BST bst, Item x) {
    link p = bst->root, h = p;

    if (bst->root == bst->z) {
        bst->root = NEW(x, bst->z, bst->z);
        return;
    }
    while (h != bst->z) {
        p = h;
        h = (KEYcmp(KEYget(x),KEYget(h->item)) == -1) ? h->l : h->r;
    }
    h = NEW(x, bst->z, bst->z);
    if (KEYcmp(KEYget(x), KEYget(p->item)) == -1)
        p->l = h;
    else
        p->r = h;
}

static link insertR(link h, Item x, link z) {
    if (h == z)
        return NEW(x, z, z);
    if (KEYcmp(KEYget(x), KEYget(h->item))==-1)
        h->l = insertR(h->l, x, z);
    else
        h->r = insertR(h->r, x, z);
    
    return h;
}

void BSTinsert_leafR(BST bst, Item x) {
    bst->root = insertR(bst->root, x, bst->z);
}

static link insertT(link h, Item x, link z) {
    if (h == z)
        return NEW(x, z, z);
    if (KEYcmp(KEYget(x), KEYget(h->item)) == -1) {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
    } else {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
    }

    return h;
}

void BSTinsert_root(BST bst, Item x) {
    bst->root = insertT(bst->root, x, bst->z);
}

Item searchR(link h, Key k, link z) {
    int cmp;

    if (h == z)
        return ITEMsetNull();
    cmp = KEYcmp(k, KEYget(h->item));
    if (cmp == 0)
        return h->item;
    if (cmp == -1)
        return searchR(h->l, k, z);
    
    return searchR(h->r, k, z);
}

Item BSTsearch(BST bst, Key k) {
    return searchR(bst->root, k, bst->z);
}

Item minR(link h, link z) {
    if (h == z)
        return ITEMsetNull();
    if (h->l == z)
        return (h->item);
    
    return minR(h->l, z);
}

Item BSTmin(BST bst) {
    return minR(bst->root, bst->z);
}

Item maxR(link h, link z) {
    if (h == z)
        return ITEMsetNull();
    if (h->r == z)
        return (h->item);
    
    return maxR(h->r, z);
}

Item BSTmax(BST bst) {
    return maxR(bst->root, bst->z);
}

static void treePrintR(link h, link z, int strategy) {
    if (h == z)
    return;
    if (strategy == PREORDER)
        ITEMstore(h->item);
    treePrintR(h->l, z, strategy);
    if (strategy == INORDER)
        ITEMstore(h->item);
    treePrintR(h->r, z, strategy);
    if (strategy == POSTORDER)
        ITEMstore(h->item);
}

void BSTvisit(BST bst, int strategy) {
    if (BSTempty(bst))
        return;
    treePrintR(bst->root, bst->z, strategy);
}

link rotL(link h) {
    link x = h->r;

    h->r = x->l;
    x->l = h;

    return x;
}

link rotR(link h) {
    link x = h->l;

    h->l = x->r;
    x->r = h;

    return x;
}
