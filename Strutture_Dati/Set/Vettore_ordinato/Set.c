#include "Set.h"

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
        if (i >= size1)                         /* primo set terminato */
            s->v[k] = s2->v[j++];
        else if (j >= size2)                    /* secondo set terminato */
            s->v[k] = s1->v[i++];
        else if (ITEMless(s1->v[i], s2->v[j]))  /* primo minore del secondo */
            s->v[k] = s1->v[i++];
        else if (ITEMless(s2->v[j], s1->v[i]))  /* secondo minore del primo */
            s->v[k] = s2->v[j++];
        else {                                  /* i due valori sono uguali */
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
    while ((i < size1) && (j < size2)) {        /* nessuno dei due è terminato */
        if (ITEMeq(s1->v[i], s2->v[j])) {       /* se uguali, inserisci */
            s->v[k++] = s1->v[i++]; 
            j++;
        }
        else if (ITEMless(s1->v[i], s2->v[j]))  /* se primo minore del secondo */
            i++;
        else                                    /* se secondo minore del primo */
            j++;
    }
    s->N = k;

    return s;
}
