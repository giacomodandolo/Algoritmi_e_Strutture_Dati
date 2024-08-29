#ifndef GRAPH_H
#include "General.h"
#include "ST.h"
#define MAX_LEN 30

typedef struct graph_t *Graph;
typedef struct edge_t Edge;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
int GRAPHgetV(Graph G);
Edge **EDGEvectInit(int V);
Graph GRAPHfile(char *filename);
void GRAPHprint(Graph G);
void GRAPHremoveE(Graph G, int v, int w);
int GRAPHdfsFindB(Graph G, int id, Edge **B, int *cntT);
void EDGEdag(Graph G, Edge **B, int cnt, int cntT);
void DAGrts(Graph D);

#endif