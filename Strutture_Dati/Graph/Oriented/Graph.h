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
void GRAPHspD(Graph G, int id);
void GRAPHspBF(Graph G, int id);

/* ORDINAMENTO TOPOLOGICO (DAG) */
void TSdfsR(Graph G, int v, int *ts, int *pre, int *time);
void DAGrts(Graph G);

#endif