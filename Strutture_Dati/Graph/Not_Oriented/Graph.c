#include "Graph.h"

struct graph {
    int V; 
    int E; 
    int **madj; 
    ST tab;
};

static int **MATRIXinit(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    
    for (i = 0; i < r; i++) 
        t[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    
    return t;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    
    e.v = v; 
    e.w = w; 
    e.wt = wt;
    
    return e;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);

    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    G->tab = STinit(V);

    return G;
}

void GRAPHfree(Graph G) {
    int i;

    for (i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}


Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for (i = 0; i < V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }
    while(fscanf(fin,"%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);      
    }

    return G;
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    GRAPHedges(G, a);
    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1; 
    G->madj[v][w] = wt;
    G->madj[w][v] = 1; 
    G->madj[w][v] = wt;
}

static void removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    if (G->madj[v][w] != 0)
        G->E--;
    G->madj[v][w] = 0;
    G->madj[w][v] = 0;
}

void GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v = 0; v < G->V; v++)
        for (w = w + 1; w < G->V; w++)
            if (G->madj[v][w] != 0)
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
    return;
}

int GRAPHgetIndex(Graph G, char *label) {
    int id;

    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STcount(G->tab);
        STinsert(G->tab, label, id);
    }

    return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

static int pathR(Graph G, int v, int w, int *visited) {
    int t;

    if (v == w)
        return 1;
    visited[v] = 1;
    for (t = 0 ; t < G->V ; t++)
        if (G->madj[v][t] == 1)
            if (visited[t] == 0)
                if (pathR(G, t, w, visited)) {
                    printf("(%s, %s) in path\n",    STsearchByIndex(G->tab, v), 
                                                    STsearchByIndex(G->tab, t));
                    return 1;
                }
    
    return 0;
}

static int pathRH(Graph G, int v, int w, int d, int *visited) {
    int t;
    
    if (v == w) {
        if (d == 0)
            return 1;
        else 
            return 0;
    }
    visited[v] = 1;
    for (t = 0 ; t < G->V ; t++)
        if (G->madj[v][t] == 1)
            if (visited[t] == 0)
                if (pathRH(G, t, w, d-1, visited)) {
                    printf("(%s, %s) in path \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
                    return 1;
                }
    visited[v] = 0;

    return 0;
}

void GRAPHpath(Graph G, int id1, int id2) {
    int t, found, *visited;

    visited = malloc(G->V*sizeof(int));
    for (t = 0; t < G->V; t++)
        visited[t] = 0;
    if (id1 < 0 || id2 < 0) 
        return;
    found = pathR(G, id1, id2, visited);
    if (found == 0) 
        printf("\n Path not found!\n");
}

void GRAPHpathH(Graph G, int id1, int id2) {
    int t, found, *visited;

    visited = malloc(G->V*sizeof(int));
    for (t = 0; t < G->V; t++)
        visited[t] = 0;
    if (id1 < 0 || id2 < 0) 
        return;
    found = pathRH(G, id1, id2, G->V-1, visited);
    if (found == 0) 
        printf("\n Path not found!\n");
}

static void dfsRcc(Graph G, int v, int id, int *cc) {
    link t;

    cc[v] = id;
    for (t = G->ladj[v]; t != G->z; t = t->next)
        if (cc[t->v] == -1)
            dfsRcc(G, t->v, id, cc);
}

int GRAPHcc(Graph G) {
    int v, id = 0, *cc;
    
    cc = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) 
        cc[v] = -1;
    for (v = 0; v < G->V; v++)
        if (cc[v] == -1) 
            dfsRcc(G, v, id++, cc);
    
    printf("Connected component(s) \n");
    for (v = 0; v < G->V; v++)
        printf("node %s in cc %d\n", STsearchByIndex(G->tab,v), cc[v]);

    return id;
}
