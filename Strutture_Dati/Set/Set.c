#include "Set.h"

/* --- SET CON VETTORE ORDINATO --- */

struct set {
    Item *v;
    int N;
};

SET SETinit(int maxN) {
    SET s = malloc(sizeof *s);

    s->v = malloc(maxN*sizeof(Item));
    s->N=0;

    return s;
}

void SETfree(SET s) {
    free(s->v);
    free(s);
}

int SETsearch(SET s, Key k) {
    int l = 0, m, r = s->N-1;

    while (l <= r) {
        m = l + (r-l)/2;
        if (KEYeq(KEYget(s->v[m]), k))
            return 1;
        if (KEYless(KEYget(s->v[m]), k))
            l = m+1;
        else
            r = m-1;
    }

    return 0;
}

SET SETunion(SET s1, SET s2) {
    int i = 0, j = 0, k = 0, size1 = SETsize(s1), size2 = SETsize(s2);
    SET s;

    s = SETinit(size1+size2);
    for(k = 0; (i < size1) || (j < size2); k++)
        if (i >= size1) 
            s->v[k] = s2->v[j++];
        else if (j >= size2) 
            s->v[k] = s1->v[i++];
        else if (ITEMless(s1->v[i], s2->v[j]))
            s->v[k] = s1->v[i++];
        else if (ITEMless(s2->v[j], s1->v[i]))
            s->v[k] = s2->v[j++];
        else { 
            s->v[k] = s1->v[i++]; 
            j++; 
        }
    s->N = k;

    return s;
}

SET SETintersection(SET s1, SET s2) {
    int i = 0, j = 0, k = 0, size1 = SETsize(s1), size2 = SETsize(s2), minsize;
    SET s;

    minsize = min(size1, size2);
    s = SETinit(minsize);
    while ((i < size1) && (j < size2)) {
        if (ITEMeq(s1->v[i], s2->v[j])) {
            s->v[k++] = s1->v[i++]; 
            j++;
        }
        else if (ITEMless(s1->v[i], s2->v[j])) 
            i++;
        else 
            j++;
    }
    s->N = k;

    return s;
}

/* --- SET CON LISTA NON ORDINATA --- */
typedef struct SETnode *link;
struct set {
    link head;
    int N;
};
struct setNode {
    Item val;
    link next;
};

SET SETinit(int maxN) {
    SET s = malloc(sizeof *s);
    
    s->head = NULL;
    s->N = 0;
    
    return s;
}

void SETfree(SET s) {
    link x, t;

    for (x = s->head; x != NULL; x = t) {
        t = x->next; 
        free(x);
    }
    free(s);
}

int SETsearch(SET s, Key k) {
    link x;

    x = s->head;
    while (x != NULL) {
        if (KEYeq(key(x->val), k))
            return 1;
        x = x->next;
    }
    return 0;
}

SET SETunion(SET s1, SET s2) {
    link x1, x2; 
    int founds2, counts2 = 0;
    SET s = SETinit(s1->N + s2->N);
    
    x1 = s1->head;
    while (x1 != NULL) {
        SETfill(s, x1->val); 
        x1 = x1->next;
    }
    for (x2 = s2->head; x2 != NULL; x2 = x2->next) {
        x1 = s1->head;
        founds2 = 0;
        while (x1 != NULL) {
            if (ITEMeq(x1->val, x2->val)) 
                founds2 = 1;
            x1 = x1->next;
        }
        if (founds2 == 0) {
            SETfill(s, x2->val); counts2++; }
    }
    s->N = s1->N + counts2;

    return s;
}

SET SETintersection(SET s1, SET s2) { 
    link x1, x2; 
    int counts=0; 
    SET s;
    
    s = SETinit(s1->N + s2->N);
    x1 = s1->head;
    while (x1 != NULL) {
        x2 = s2->head;
        while (x2 != NULL) {
            if (ITEMeq(x1->val, x2->val)) {
                SETfill(s, x1->val); 
                counts++; 
                break;
            }
            x2 = x2->next;
        }
        x1 = x1->next;
    }
    s->N = counts;

    return s;
}