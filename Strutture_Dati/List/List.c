#include "List.h"

Key KEYget(Item d) {
    return d;
}

int KEYeq(Key k1, Key k2) {
    return k1 == k2;
}

int KEYless(Key k1, Key k2) {
    return k1 < k2;
}

int KEYgreater(Key k1, Key k2) {
    return k1 > k2;
}

void ITEMdisplay(Item d) {
    printf("VAL = %d\n", d);
}

Item ITEMsetvoid() {
    return 0;
}

link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;

    return x;
}

link listInsHead(link h, Item val) {
    h = newNode(val, h);

    return h;
}

void listInsHeadP(link *hp, Item val) {
    *hp = newNode(val, *hp);
}

link listInsTail(link h, Item val) {
    link x;

    if (h == NULL)
        return newNode(val, NULL);
    for (x = h; x->next != NULL; x = x->next);
    x->next = newNode(val, NULL);
    
    return h;
}

void listInsTailP(link *hp, Item val) {
    link x = *hp;
    
    if (x == NULL)
        *hp = newNode(val, NULL);
    else { 
        for (; x->next != NULL; x = x->next);
        x->next = newNode(val, NULL);
    }
}

void listInsTailP(link *hp, Item val) {
    link *xp = hp;
    
    while (*xp != NULL)
        xp = &((*xp)->next);
    *xp = newNode(val, NULL);
}

void listInsTFast(link *hp, link *tp, Item val) {
    if (*hp == NULL)
        *hp = *tp = newNode(val, NULL);
    else {
        (*tp)->next = newNode(val, NULL);
        *tp = (*tp)->next;
    }
}

link SortListIns(link h, Item val) {
    link x, p;
    Key k = KEYget(val);

    if (h == NULL || KEYgreater(KEYget(h->val), k))
        return newNode(val, h);
    for (x = h->next, p = h; x != NULL && KEYgreater(k, KEYget(x->val)); p = x, x = x->next);
    p->next = newNode(val, x);
    
    return h;
}

void listTravR(link h) {
    if (h == NULL)
        return;
    ITEMdisplay(h->val);
    listTravR(h->next);
}

void listRevTravR(link h) {
    if (h == NULL)
        return;
    listRevTravR(h->next);
    ITEMdisplay(h->val);
}

Item listSearch(link h, Key k) {
    link x;

    for (x = h; x != NULL; x = x->next)
        if (KEYeq(KEYget(x->val), k))
            return x->val;

    return ITEMsetvoid();
}

Item SortListSearch(link h, Key k) {
    link x;

    for (x = h; x != NULL && KEYgeq(k, KEYget(x->val)); x = x->next)
        if (KEYeq(KEYget(x->val), k))
            return x->val;
    
    return ITEMsetvoid();
}

link listDelHead(link h) {
    link t = h;

    if (h == NULL)
        return NULL;
    h = h->next;
    free(t);

    return h;
}

link listDelKey(link h, Key k) {
    link x, p;

    if (h == NULL)
        return NULL;
    for (x = h, p = NULL; x != NULL; p = x, x = x->next) {
        if (KEYeq(KEYget(x->val), k)) {
            if (x == h)
                h = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }

    return h;
}

link listDelKeyR(link x, Key k) {
    link t;

    if (x == NULL)
        return NULL;
    if (KEYeq(KEYget(x->val), k)) {
        t = x->next;
        free(x);
        return t;
    }
    x->next = listDelKeyR(x->next, k);
    
    return x;
}

link SortListDel(link h, Key k) {
    link x, p;

    if (h == NULL) 
        return NULL;
    for (x = h, p = NULL; x != NULL && KEYgeq(k, KEYget(x->val)); p = x, x = x->next) {
        if (KEYeq(KEYget(x->val), k)) {
            if (x == h) 
                h = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }

    return h;
}

Item listExtrHeadP(link *hp) {
    link t = *hp;
    Item tmp;

    if (t == NULL)
        return ITEMsetvoid();
    tmp = t->val;
    *hp = t->next;
    free(t);

    return tmp;
}

Item listExtrKeyP(link *hp, Key k) {
    link *xp, t;
    Item i = ITEMsetvoid();

    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (KEYeq(KEYget((*xp)->val), k)){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    
    return i;
}

link listReverseF(link x) {
    link y = x, r = NULL;
    Item tmp;
    
    while (y != NULL) {
        tmp = listExtrHeadP(&y);
        r = listInsHead(r, tmp);
    }
    
    return r;
}

link listReverseF(link x) {
    link t, y = x, r = NULL;

    while (y != NULL) {
        t = y->next;
        y->next = r;
        r = y;
        y = t;
    }

    return r;
}

link listSortF(link h) {
    link y = h, r = NULL;
    Item tmp;

    while (y != NULL) {
        tmp = listExtrHeadP(&y);
        r = SortListIns(r, tmp);
    }

    return r;
}
