#include "general.h"

#ifndef NODO_H
#define NODO_H

typedef struct nodo_t *Nodo;
typedef enum {N, S, O, E};

Nodo nodo_init(int default_val);
void nodo_free(Nodo n);
Nodo nodo_set(Nodo n, int a, int b);
int nodo_is_null(Nodo n);
int nodo_is_inizio(Nodo n);
Nodo nodo_copy(Nodo n1, Nodo n2);
int nodo_cmp(Nodo n1, Nodo n2);
int nodo_get(Nodo n, int i);

#endif /* NODO_H */