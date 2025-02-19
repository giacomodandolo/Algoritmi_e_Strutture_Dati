#include "griglia.h"

struct griglia_t {
    Nodo **m;
    int N;
} griglia_val;

struct mosse_t {
    int *direzione;
    int n_mosse;
};

Griglia griglia_init(int n) {
    int i, j;
    Griglia new;

    new = (Griglia) malloc(sizeof(griglia_val));
    new->N = n;
    new->m = (Nodo**) malloc(n*sizeof(Nodo*));
    for (i = 0; i < n; i++) {
        new->m[i] = (Nodo*) malloc(n*sizeof(Nodo));
        for (j = 0; j < n; j++) {
            new->m[i][j] = nodo_init(-1);
        }
    }

    return new;
}

/*
    NB: vXYZ, con X coordinata, Y seconda coordinata,
        Z indice della componente nel nodo (1 o 2),
        e vXYZ identifica la direzione della componente
        (N=0, S=1, O=2, E=3)

    Formato file "griglia.txt":
    N
    v111,v112 v121,v122 ......... v1N1,v1N2
    v211,v212 ......... ......... .........
    ......... ......... ......... .........
    vN11,vN12 vN21,vN22 ......... vNN1,vNN2

*/
Griglia griglia_file(FILE* file) {
    int i, j, n, a, b;
    Nodo tmp;
    Griglia g;

    fscanf(file, "%d", &n);
    g = griglia_init(n);
    for (i = 0; i < n; i++) {
        
        for (j = 0; j < n; j++) {
            tmp = g->m[i][j];
            fscanf(file, "%d,%d", &a, &b);
            nodo_set(tmp, a, b);
        }
    }

    return g;
}

Griglia griglia_copy(Griglia g) {
    int i, j, a, b;
    Griglia copy;

    copy = griglia_init(g->N);
    for (i = 0; i < g->N; i++)
        for (j = 0; j < g->N; j++) {
            a = nodo_get(g->m[i][j], 0);
            b = nodo_get(g->m[i][j], 1);
            copy->m[i][j] = nodo_set(copy->m[i][j], a, b);
        }

    return copy;
}

void griglia_free(Griglia g) {
    int i, j;

    for (i = 0; i < g->N; i++) {
        for (j = 0; j < g->N; j++)
            nodo_free(g->m[i][j]);
        free(g->m[i]);
    }
    free(g);
}

static int test_direction(Griglia g, int i, int j, int dir) {
    switch(dir) {
        case N:
            /* Nord */
            if (i > 0)
                if (nodo_is_null(g->m[i-1][j]) == TRUE)
                    return TRUE;
            break;
        case S:
            /* Sud */
            if (i < g->N-1)
                if (nodo_is_null(g->m[i+1][j]) == TRUE)
                    return TRUE;
            break;
        case O:
            /* Ovest */
            if (j > 0)
                if (nodo_is_null(g->m[i][j-1]) == TRUE)
                    return TRUE;
            break;
        case E:
            /* Est */
            if (j < g->N-1)
                if (nodo_is_null(g->m[i][j+1]) == TRUE)
                    return TRUE;
            break;
        default:
            break;
    }
    return FALSE;
}

static int testa_mossa(Griglia g, int dir) {
    int i, j;

    for (i = 0; i < g->N; i++)
        for (j = 0; j < g->N; j++)
            if (test_direction(g, i, j, dir) == TRUE)
                return TRUE;
    
    return FALSE;
}

static void muovi_nodo(Griglia *g, int i, int j, int dir) {
    switch(dir) {
        case N:
            /* Nord */
            nodo_copy((*g)->m[i-1][j], (*g)->m[i][j]);
            break;
        case S:
            /* Sud */
            nodo_copy((*g)->m[i+1][j], (*g)->m[i][j]);
            break;
        case O:
            /* Ovest */
            nodo_copy((*g)->m[i][j-1], (*g)->m[i][j]);
            break;
        case E:
            /* Est */
            nodo_copy((*g)->m[i][j+1], (*g)->m[i][j]);
            break;
        default:
            break;
    }
    nodo_set((*g)->m[i][j], -1, -1);
}

static Griglia esegui_mossa(Griglia g, int dir) {
    int i, j;
    Griglia copy;

    copy = griglia_copy(g);
    for (i = 0; i < g->N; i++)
        for (j = 0; j < g->N; j++)
            if (test_direction(g, i, j, dir))
                muovi_nodo(&copy, i, j, dir);
    
    return copy;
}

static int check_directions(Griglia g, int *i, int *j, int *prev_val) {
    int test;
    
    switch((*prev_val)) {
        case N:
            /* Nord */
            if ((*i) < 1)
                return FALSE;
            test = nodo_cmp(g->m[(*i)][(*j)], g->m[(*i)-1][(*j)]);
            if (test != -1) {
                (*prev_val) = nodo_get(g->m[(*i)-1][(*j)], 1-test);
                (*i) = (*i)-1;
            }
            break;
        case S:
            /* Sud */
            if ((*i) >= g->N-1)
                return FALSE;
            test = nodo_cmp(g->m[(*i)][(*j)], g->m[(*i)+1][(*j)]);
            if (test != -1) {
                (*prev_val) = nodo_get(g->m[(*i)+1][(*j)], 1-test);
                (*i) = (*i)+1;
            }
            break;
        case O:
            /* Ovest */
            if ((*j) < 1)
                return FALSE;
            test = nodo_cmp(g->m[(*i)][(*j)], g->m[(*i)][(*j)-1]);
            if (test != -1) {
                (*prev_val) = nodo_get(g->m[(*i)][(*j)-1], 1-test);
                (*j) = (*j)-1;
            }
            break;
        case E:
            /* Est */
            if ((*j) > g->N-1)
                return FALSE;
            test = nodo_cmp(g->m[(*i)][(*j)], g->m[(*i)][(*j)+1]);
            if (test != -1) {
                (*prev_val) = nodo_get(g->m[(*i)][(*j)+1], 1-test);
                (*j) = (*j)+1;
            }
            break;
        default:
            test = -1;
            break;
    }

    if (test != -1)
        return TRUE;
    return FALSE;
}

static int controlla_percorso(Griglia g) {
    int i, j, prev_i, prev_j, prev_val, i_end, j_end, n_found;

    n_found = 0;
    for (i = 0; i < g->N; i++)
        for (j = 0; j < g->N; j++)
            if (nodo_is_inizio(g->m[i][j]) == TRUE) {
                if (n_found == 0) {
                    prev_i = i;
                    prev_j = j;
                    prev_val = nodo_get(g->m[i][j], 0);
                }
                if (n_found == 1) {
                    i_end = i;
                    j_end = j;
                }
                n_found++;
            }
    
    /* 
        Non ha esattamente inizio e fine, 
        ma ha solo inizio oppure un numero
        oltre a 2 di inizi e fine
    */
    if (n_found != 2)
        return FALSE;
    
    while(prev_i != i_end || prev_j != j_end) {
        if(check_directions(g, &prev_i, &prev_j, &prev_val) == FALSE)
            return FALSE;
    }

    return TRUE;
}

int controlla_mosse(Griglia *g, Mosse m) {
    int i, direzione;

    for (i = 0; i < mosse_get_n(m); i++) {
        direzione = mosse_get_dir(m, i);
        if (testa_mossa(*g, direzione) == TRUE) {
            (*g) = esegui_mossa(*g, direzione);
            continue;
        }
        return FALSE;
    }

    return controlla_percorso(*g);
}

static Mosse trova_soluzione_r(Griglia g, int pos, Mosse mosse, int M, int *found) {
    int dir;

    if (pos <= M) {
        if (controlla_percorso(g) == TRUE) {
            (*found) = TRUE;
            return mosse;
        }
    }

    if (pos >= M)
        return mosse;

    for (dir = 0; dir < N_DIR && (*found) == FALSE && pos < M; dir++) {
        if (testa_mossa(g, dir) == TRUE) {
            /* Nuova scelta */
            mosse_add(mosse, pos, dir);
            g = esegui_mossa(g, dir);
            /* Ricorsione */
            mosse = trova_soluzione_r(g, pos+1, mosse, M, found);
            /* Backtrack */
            if ((*found) == FALSE)
                mosse_remove(mosse, pos, dir);
            g = esegui_mossa(g, mosse_inversa(dir));
        }
    }

    return mosse;
}

void trova_soluzione(Griglia g, int M) {
    int found;
    Mosse mosse;

    mosse = mosse_init(M, -1);
    found = FALSE;

    mosse = trova_soluzione_r(g, 0, mosse, M, &found);

    if (found == TRUE)
        mosse_stampa(mosse);
    else 
        fprintf(stdout, "Non e' stata trovata una sequenza di mosse valide.\n");
    
    return;
}