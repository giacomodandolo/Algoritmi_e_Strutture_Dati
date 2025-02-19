#include "nodo.h"
#define N_COMP 2

struct nodo_t {
    int* val;
} nodo_val;

Nodo nodo_init(int default_val) {
    int i;
    Nodo new;

    new = (Nodo) malloc(sizeof(nodo_val));
    new->val = (int*) malloc(sizeof(int));
    for (i = 0; i < N_COMP; i++)
        new->val[i] = default_val;

    return new;
}

void nodo_free(Nodo n) {
    free(n);
}

Nodo nodo_set(Nodo n, int a, int b) {
    n->val[0] = a;
    n->val[1] = b;

    return n;
}

static int check_components(int a, int b) {
    switch(a) {
        case N:
            if (b == S)
                return TRUE;
            break;
        case S:
            if (b == N)
                return TRUE;
            break;
        case O:
            if (b == E)
                return TRUE;
            break;
        case E:
            if (b == O)
                return TRUE;
            break;
        default:
            return FALSE;
    }
    return FALSE;
}

int nodo_is_null(Nodo n) {
    return (n->val[0] == -1 && n->val[1] == -1);
}

Nodo nodo_copy(Nodo n1, Nodo n2) {
    n1->val[0] = n2->val[0];
    n1->val[1] = n2->val[1];

    return n1;
}

int nodo_is_inizio(Nodo n) {
    return (n->val[0] != -1 && n->val[1] == -1);
}

int nodo_cmp(Nodo n1, Nodo n2) {
    int i, j;

    for (i = 0; i < N_COMP; i++) // per ogni componente di n1
        for (j = 0; j < N_COMP; j++) // per ogni componente di n2
            if (check_components(n1->val[i], n2->val[j]) == TRUE)
                return j;
    
    return -1;
}

int nodo_get(Nodo n, int i) {
    return n->val[i];
}