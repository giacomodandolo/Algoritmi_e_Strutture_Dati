#include "List.h"

typedef struct nodeCT_t {
    Titolo *item;
    linkCT next;
} nodeCT, *linkCT;

typedef struct collTitolo_t {
    linkCT h, z;
} *List;

static linkCT NEW(Titolo *item, linkCT next) {
    linkCT x;

    x = (linkCT) malloc(sizeof(nodeCT));
    x->item = item;
    x->next = next;

    return x;
}

List LISTinit() {
    List x;

    x = (List) malloc(sizeof(*x));
    x->z = NEW(TITOLOsetvoid(), NULL);
    x->h = x->z;

    return x;
}

Titolo *LISTsetvoid(List list) {
    return list->z->item;
}

void LISTstore(FILE* file, List l, KeyT k) {
    Titolo *t;

    t = LISTsearch(l, k);
    if (t != l->z->item)
        TITOLOstore(file, t);
}

static int LISTsearchQuot(List l, KeyT k) {
    Titolo *t;

    t = LISTsearch(l, k);

    return TITOLOgetQuot(t);
}

void LISTstoreQuot(FILE* file, List l, KeyT k) {
    Titolo *t;

    t = LISTsearch(l, k);
    if (t != l->z->item)
        fprintf(file, "%d\n", LISTsearchQuot(l, k));
}

void LISTstoreMaxMin(FILE *file, List l, KeyT k) {
    Titolo *t;

    t = LISTsearch(l, k);
    
    if (t != l->z->item)
        TITOLOstoreMaxMin(file, t);
}

void LISTstoreQuotDate(FILE *file, List l, KeyT k, KeyQ *d1, KeyQ *d2) {
    Titolo *t;

    t = LISTsearch(l, k);
    if (t != l->z->item)
        TITOLOstoreQuotDate(file, t, d1, d2);
}

List LISTinsOrd(List l, Titolo *item) {
    linkCT x, p;
    KeyT k;

    k = TITOLOgetKey(item);
    if (l->h == l->z || TITOLOcmpKey(TITOLOgetKey(l->h->item), k) > 0) {
        l->h = NEW(item, l->h);
        return l;
    }

    for (p = l->h, x = l->h->next; x != l->z && TITOLOcmpKey(TITOLOgetKey(x->item), k) < 0; p = x, x = x->next);
    p->next = NEW(item, x);

    return l;
}

Titolo *LISTsearch(List l, KeyT k) {
    linkCT x;

    for (x = l->h; x != l->z && TITOLOcmpKey(TITOLOgetKey(x->item), k) < 0; x = x->next);
    if (TITOLOcmpKey(TITOLOgetKey(x->item), k) == 0)
        return x->item;

    return l->z->item;
}

List LISTupdate(List l, KeyT k, Quot *q) {
    linkCT x;

    for (x = l->h; x != l->z && TITOLOcmpKey(TITOLOgetKey(x->item), k) < 0; x = x->next);
    
    if (TITOLOcmpKey(TITOLOgetKey(x->item), k) == 0)
        x->item = TITOLOaddQuot(x->item, q);
    
    return l;
}