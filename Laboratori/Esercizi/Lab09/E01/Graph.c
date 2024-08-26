#include "Graph.h"

typedef struct graph_t {
    int V, **madj;
    ST tab;
} *Graph;

static int **MATRIXinit(int r, int c, int v) {
    int i, j, **m;

    m = (int**) malloc(r*sizeof(int*));
    for (i = 0; i < r; i++) {
        m[i] = (int*) malloc(c*sizeof(int));
        for (j = 0; j < c; j++)
            m[i][j] = v;
    }

    return m;
}

Graph GRAPHinit(int V) {
    Graph G;

    G = (Graph) malloc(sizeof(*G));
    G->V = V;
    G->madj = MATRIXinit(V, V, 0);
    G->tab = STinit(V);

    return G;
}

Graph GRAPHfile(char *filename) {
    int i, j, V, wt;
    char c, id_1, id_2;
    Graph G;
    FILE* file;

    file = fopen(filename, "r");
    fscanf(file, "%d\n", &V);
    G = GRAPHinit(V);
    
    for (i = 0; i < V; i++) {
        fscanf(file, "%c\n", &c);
        STinsert(G->tab, c);
    }

    while (fscanf(file, "%c %c %d\n", &id_1, &id_2, &wt) == 3) {
        i = STsearch(G->tab, id_1);
        j = STsearch(G->tab, id_2);
        G->madj[i][j] = wt;
    }

    return G;
}

void GRAPHprint(Graph G) {
    int i, j;
    char c, c1, c2;
    
    printf("Numero nodi: %d\n", G->V);
    for (i = 0; i < G->V; i++) {
        c = STsearchByIndex(G->tab, i);
        printf("%d: %c\n", i, c);
    }
    printf("\n");

    printf("Archi: \n");
    for (i = 0; i < G->V; i++)
        for (j = 0; j < G->V; j++)
            if (G->madj[i][j] != 0) {
                c1 = STsearchByIndex(G->tab, i);
                c2 = STsearchByIndex(G->tab, j);
                printf("%c %c %d\n", c1, c2, G->madj[i][j]);
            }
}

