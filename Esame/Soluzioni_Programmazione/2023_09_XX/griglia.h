#ifndef GRIGLIA_H
#define GRIGLIA_H

#include "nodo.h"
#include "mosse.h"

typedef struct griglia_t *Griglia;

Griglia griglia_init(int N);
Griglia griglia_file(FILE* file);
Griglia griglia_copy(Griglia g);
int controlla_mosse(Griglia *g, Mosse m);
void trova_soluzione(Griglia g, int M);

#endif /* GRIGLIA_H */