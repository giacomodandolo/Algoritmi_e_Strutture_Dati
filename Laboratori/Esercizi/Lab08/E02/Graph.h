#ifndef GRAPH_H
#include "Item.h"
#include "ST.h"
#include "General.h"

typedef struct node_t node, *link;
typedef struct graph_t *Graph;

int adjacent(Graph G, int i, int j);
int **MATRIXinit(int r, int c, int v);
void MATRIXfree(int **m, int r);
link LISTnew(int v, int wt, link next);
link LISTinshead(int v, int wt, link h);
link LISTdelhead(link h);
void LISTfree(link* lists, int n);
void LISTprint(link h);
void LISTprintAll(Graph G);
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHinsertE(Graph G, Key v, char *net1, Key w, char *net2, int wt);
void GRAPHstore(Graph G);
void GRAPHmat2list(Graph G);
int GRAPHcheck3clique(Graph G, Key v, Key w, Key t);

#endif