#include "mosse.h"

struct mosse_t {
    int *direzione;
    int n_mosse;
} mosse_val;

Mosse mosse_init(int N, int default_val) {
    int i;
    Mosse new;

    new = (Mosse) malloc(sizeof(mosse_val));
    new->n_mosse = 0;
    new->direzione = (int*) malloc(N*sizeof(int));
    for (i = 0; i < N; i++) {
        new->direzione[i] = default_val;
    }

    return new;
}

/*
    Formato file "mosse.txt":
    N
    v1 v2 ... vN
*/
Mosse mosse_file(FILE* file) {
    int i, N, current;
    Mosse m;

    fscanf(file, "%d", &N);
    m = mosse_init(N, -1);
    for (i = 0; i < N; i++) {
        fscanf(file, "%d", &current);
        mosse_add(m, i, current);
    }

    return m;
}

int mosse_get_n(Mosse m) {
    return m->n_mosse;
}

int mosse_get_dir(Mosse m, int i) {
    return m->direzione[i];
}

void mosse_add(Mosse mosse, int i, int dir) {
    mosse->direzione[i] = dir;
    mosse->n_mosse += 1;
}

void mosse_remove(Mosse mosse, int i, int dir) {
    mosse->direzione[i] = -1;
    mosse->n_mosse -= 1;
}

static char traduci_mossa(int dir) {
    switch(dir) {
        case U:
            return 'U';
        case D:
            return 'D';
        case L:
            return 'L';
        case R:
            return 'R';
    }

    return ' ';
}

void mosse_stampa(Mosse mosse) {
    int i;

    fprintf(stdout, "Mosse = [ ");
    for (i = 0; i < mosse->n_mosse; i++)
        fprintf(stdout, "%c ", traduci_mossa(mosse->direzione[i]));
    fprintf(stdout, "]\n");

    return;
}

int mosse_inversa(int dir) {
    switch(dir) {
        case U:
            return D;
        case D:
            return U;
        case L:
            return R;
        case R:
            return L;
    }
}