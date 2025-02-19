#include "general.h"

#ifndef MOSSE_H
#define MOSSE_H

#define N_DIR 4

typedef struct mosse_t *Mosse;
typedef enum {U, D, L, R};

Mosse mosse_init(int N, int default_val);
Mosse mosse_file(FILE* file);
int mosse_get_n(Mosse m);
int mosse_get_dir(Mosse m, int i);
void mosse_add(Mosse mosse, int i, int dir);
void mosse_remove(Mosse mosse, int i, int dir);
void mosse_stampa(Mosse mosse);
int mosse_inversa(int dir);

#endif /* MOSSE_H */