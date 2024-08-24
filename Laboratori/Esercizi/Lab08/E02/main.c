#include "Graph.h"
#define MAX_FILE 50

Graph readFile(char *filename) {
    int i, V, wt;
    char id_elab1[MAX_LEN], id_net1[MAX_LEN], id_elab2[MAX_LEN], id_net2[MAX_LEN];
    Graph G;
    FILE* file;

    file = fopen(filename, "r");
    V = 0;
    while (fscanf(file, "%s %s %s %s %d", id_elab1, id_net1, id_elab2, id_net2, &wt) == 5)
        V++;
    fclose(file);

    G = GRAPHinit(2*V);
    file = fopen(filename, "r");
    for (i = 0; i < V; i++) {
        fscanf(file, "%s %s %s %s %d", id_elab1, id_net1, id_elab2, id_net2, &wt);
        GRAPHinsertE(G, id_elab1, id_net1, id_elab2, id_net2, wt);
    }
    fclose(file);

    return G;
}

int main(void) {
    Graph G;
    char filename[MAX_FILE], v[MAX_LEN], w[MAX_LEN], t[MAX_LEN];

    printf("Nome file: ");
    scanf("%s", filename);

    G = readFile(filename);
    GRAPHstore(G);

    printf("Vertice 1: ");
    scanf("%s", v);
    printf("Vertice 2: ");
    scanf("%s", w);
    printf("Vertice 3: ");
    scanf("%s", t);
    if (GRAPHcheck3clique(G, v, w, t))
        printf("Formano un sottografo completo.\n");
    else
        printf("Non formano un sottografo completo.\n");

    GRAPHmat2list(G);
    LISTprintAll(G);
    GRAPHfree(G);

    return 0;
}