#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge { 
    int v; 
    int w; 
    int wt; 
} Edge;
typedef struct graph *Graph;

/* INIZIALIZZAZIONE */
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHload(FILE *fin);

/* VISUALIZZAZIONE */
void GRAPHstore(Graph G, FILE *fout);
void GRAPHedges(Graph G, Edge *a);

/* OTTIENI INDICE */
int GRAPHgetIndex(Graph G, char *label);

/* INSERIMENTO ARCHI */
void GRAPHinsertE(Graph G, int id1, int id2, int wt);

/* RIMOZIONE ARCHI */
void GRAPHremoveE(Graph G, int id1, int id2);

/* CAMMINI */
void GRAPHpath(Graph G, int id1, int id2);
void GRAPHpathH(Graph G, int id1, int id2);

/* VISITA */
void GRAPHbfs(Graph G, int id);
void GRAPHdfs(Graph G, int id);

/* COMPONENTI CONNESSE */
int GRAPHscc(Graph G);

/* ALBERI RICOPRENTI MINIMI */
void GRAPHmstK(Graph G);
void GRAPHmstP(Graph G);

/* CAMMINO MINIMO */
void GRAPHspD(Graph G, int id) {
    int v;
    link t;
    PQ pq = PQinit(G->V);
    int *st, *d;

    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    for (v = 0; v < G->V; v++) {
        st[v] = -1;
        d[v] = maxWT;
        PQinsert(pq, d, v);
    }

    d[id] = 0;
    st[id] = id;
    PQchange(pq, d, id);

    while (!PQempty(pq)) {
        if (d[v = PQextractMin(pq, d)] != maxWT)
            for (t = G->ladj[v]; t != G->z ; t = t->next)
                if (d[v] + t->wt < d[t->v]) {
                    d[t->v] = d[v] + t->wt;
                    PQchange(pq, d, t->v);
                    st[t->v] = v;
                }
    }

    printf("\n Shortest path tree\n");
    for (v = 0; v < G->V; v++)
        printf("parent of %s is %s \n", STsearchByIndex(G->tab, v),
                                        STsearchByIndex (G->tab, st[v]));
    
    printf("\n Min.dist. from %s\n", STsearchByIndex(G->tab, s));
    for (v = 0; v < G->V; v++)
        printf("%s: %d\n", STsearchByIndex(G->tab, v), d[v]);
    PQfree(pq);
}

#endif