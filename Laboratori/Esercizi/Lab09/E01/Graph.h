#ifndef GRAPH_H
#include "General.h"
#include "ST.h"
#define MAX_LEN 30

typedef struct graph_t *Graph;

Graph GRAPHinit(int V);
Graph GRAPHfile(char *filename);
void GRAPHprint(Graph G);

#endif