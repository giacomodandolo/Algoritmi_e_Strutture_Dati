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
int GRAPHpath(Graph G, int id1, int id2);
void GRAPHpathH(Graph G, int id1, int id2);
void GRAPHbfs(Graph G, int id);
void GRAPHdfs(Graph G, int id);

/* COMPONENTI CONNESSE */
int GRAPHcc(Graph G);

#endif