#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 30

typedef struct edge {
    int u;
    int v;
} Edge;

typedef struct graph {
    int N;
    int nE;
    Edge *E;
} Graph;

Graph* graph_init(FILE *file) {
    int i;
    Graph* G;

    G = (Graph*) malloc(sizeof(Graph));
    fscanf(file, "%d %d", &(G->N), &(G->nE));
    G->E = (Edge*) malloc(G->nE*sizeof(Edge));
    for (i = 0; i < G->nE; i++) {
        fscanf(file, "%d %d", &(G->E[i].u), &(G->E[i].v));
    }
    return G;
}

void print_vc(int *sol, int n) {
    int i;

    printf("(");
    for (i = 0; i < n-1; i++) {
        printf("%d, ", sol[i]);
    }
    printf("%d)", sol[n-1]);
}

int is_vc(Graph *G, int *sol, int n) {
    int i, j, *occ;

    occ = (int*) calloc(G->nE, sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < G->nE; j++)
            if (G->E[j].u == sol[i] || G->E[j].v == sol[i])
                occ[j] = 1;

    for (i = 0; i < G->N; i++) {
        if (occ[i] == 0)
            return 0;
    }

    return 1;
}

/* Soluzione con powerset in versione divide et impera */
/*
int powerset_vc(int pos, Graph *G, int *sol, int start, int cnt) {
    int i;

    if (start >= G->N) {
        if (is_vc(G, sol, pos)) {
            print_vc(sol, pos);
            return cnt+1;
        }
        return cnt;
    }

    for (i = start; i < G->N; i++) {
        sol[pos] = i;
        cnt = powerset_vc(pos+1, G, sol, i+1, cnt);
    }
    cnt = powerset_vc(pos, G, sol, G->N, cnt);
    return cnt;
}
*/

/* Soluzione con powerset in versione combinazioni semplici */
int powerset_vcR(int pos, Graph *G, int *sol, int j, int start) {
    int cnt = 0, i;
    if (pos >= j) {
        if (is_vc(G, sol, j)) {
            print_vc(sol, j);
            return 1;
        }
        return 0;
    }

    for (i = start; i < G->N; i++) {
        sol[pos] = i;
        cnt += powerset_vcR(pos+1, G, sol, j, i+1);
    }
    return cnt;
}

int powerset_vc(Graph *G, int *sol) {
    int cnt = 0, j;

    for (j = 1; j <= G->N; j++) {
        cnt += powerset_vcR(0, G, sol, j, 0);
    }
    return cnt;
}

int main(void) {
    int *sol;
    char filename[MAX_LENGTH];
    Graph *G;
    FILE *file;

    printf("Nome file: ");
    scanf("%s", filename);
    file = fopen(filename, "r");

    G = graph_init(file);
    sol = (int*) malloc(G->N*sizeof(int));

    // printf("\nNumero di vertex covers: %d", powerset_vc(0, G, sol, 0, 0));

    printf("\nNumero di vertex covers: %d", powerset_vc(G, sol));

    fclose(file);
    return 0;
}