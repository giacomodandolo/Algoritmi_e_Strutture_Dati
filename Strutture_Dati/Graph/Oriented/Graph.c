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
}

static void removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    if (G->madj[v][w] != 0)
        G->E--;
    G->madj[v][w] = 0;
}

void GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v = 0; v < G->V; v++)
        for (w = 0; w < G->V; w++)
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
                    printf("(%s, %s) in path\n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
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
    found = pathR(G, id1, id2, G->V-1, visited);
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

Graph GRAPHreverse(Graph G) {
    int v;
    link t;
    Graph R = GRAPHinit(G->V);

    for (v = 0; v < G->V; v++)
        for (t = G->ladj[v]; t != G->z; t = t->next)
            GRAPHinsertE(R, t->v, v);
    return R;
}

static void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post) {
    link t;

    scc[w] = time1;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (scc[t->v] == -1)
            SCCdfsR(G, t->v, scc, time0, time1, post);
    post[(*time0)++]= w;
}

int GRAPHscc(Graph G) {
    int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
    Graph R = GRAPHreverse(G);

    sccG = malloc(G->V * sizeof(int));
    sccR = malloc(G->V * sizeof(int));
    postG = malloc(G->V * sizeof(int));
    postR = malloc(G->V * sizeof(int));

    for (v = 0; v < G->V; v++) {
        sccG[v] = -1; 
        sccR[v] = -1; 
        postG[v] = -1; 
        postR[v] = -1;
    }
    for (v=0; v < G->V; v++)
        if (sccR[v] == -1)
            SCCdfsR(R, v, sccR, &time0, time1, postR);
    
    time0 = 0; 
    time1 = 0;
    for (v = G->V-1; v >= 0; v--)
        if (sccG[postR[v]] == -1){
            SCCdfsR(G, postR[v], sccG, &time0, time1, postG);
            time1++;
        }
    
    printf("strongly connected components \n");
    for (v = 0; v < G->V; v++)
        printf("node %s in scc %d\n", STsearchByIndex(G->tab,v), sccG[v]);
    
    return time1;
}

static int mstE(Graph G, Edge *mst, Edge *a) {
    int i, k;

    GRAPHedges(G, a);
    sort(a, 0, G->E-1);
    UFinit(G->V);
    for (i = 0, k = 0; i < G->E && k < G->V-1; i++)
        if (!UFfind(a[i].v, a[i].w)) { 
            UFunion(a[i].v, a[i].w); 
            mst[k++] = a[i];
        }
    return k;
}

void GRAPHmstK(Graph G) {
    int i, k, weight = 0;
    Edge *mst = malloc((G->V-1) * sizeof(Edge)); 
    Edge *a = malloc(G->E * sizeof(Edge));  

    k = mstE(G, mst, a);

    printf("\nEdges in the MST: \n");
    for (i=0; i < k; i++) {
        printf("(%s - %s) \n",  STsearchByIndex(G->tab, mst[i].v), 
                                STsearchByIndex(G->tab, mst[i].w));
        weight += mst[i].wt;
    }
    printf("minimum weight: %d\n", weight);
}

static void mstV(Graph G, int *st, int *wt) {
    int v, w, min, *fr = malloc(G->V*sizeof(int));
    
    for (v=0; v < G->V; v++) { 
        st[v] = -1; 
        fr[v] = v;  
        wt[v] = maxWT; 
    }
    st[0] = 0;   
    wt[0] = 0;   
    wt[G->V] = maxWT;

    for (min = 0; min != G->V; ) {
        v = min;  
        st[min] = fr[min];
        for (w = 0, min = G->V; w < G->V; w++)
            if (st[w] == -1) {
                if (G->madj[v][w] < wt[w]) { 
                    wt[w] = G->madj[v][w]; 
                    fr[w] = v; 
                }
                if (wt[w] < wt[min]) 
                    min = w;
            }
    }
}

void GRAPHmstP(Graph G) {
    int v, *st, *wt, weight = 0;

    st = malloc(G->V*sizeof(int)); 
    wt = malloc((G->V+1)*sizeof(int));

    mstV(G, st, wt);

    printf("\nEdges in the MST: \n");

    for (v = 0; v < G->V; v++) {
        if (st[v] != v) {
            printf("(%s-%s)\n", STsearchByIndex(G->tab, st[v]),
                                STsearchByIndex(G->tab, v));
            weight += wt[v];
        }
    }
    printf("\nminimum weight: %d\n", weight);
}

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

void GRAPHspBF(Graph G, int id) {
    int v, i, negcycfound;
    link t;
    int *st, *d;

    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));

    for (v = 0; v < G->V; v++) {
        st[v]= -1;
        d[v] = maxWT;
    }
    d[id] = 0;
    st[id] = id;

    for (i = 0; i < G->V-1; i++)
        for (v = 0; v < G->V; v++)
            if (d[v] < maxWT)
                for (t = G->ladj[v]; t != G->z ; t = t->next)
                    if (d[t->v] > d[v] + t->wt) {
                        d[t->v] = d[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    for (v = 0; v < G->V; v++)
        if (d[v] < maxWT)
            for (t = G->ladj[v]; t != G->z ; t = t->next)
                if (d[t->v] > d[v] + t->wt)
                    negcycfound = 1;

    if (negcycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %s is %s \n", STsearchByIndex(G->tab, v),
                                            STsearchByIndex(G->tab, st[v]));
        printf("\n Min.dist. from %s\n", STsearchByIndex (G->tab, s));
        for (v = 0; v < G->V; v++)
        printf("%s: %d\n", STsearchByIndex (G->tab, v), d[v]);
    }
    else
        printf("\n Negative cycle found!\n");
}

void TSdfsR(Graph G, int v, int *ts, int *pre, int *time) {
    link t; 
    pre[v] = 0;

    for (t = G->ladj[v]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(G, t->v, ts, pre, time);

    ts[(*time)++] = v;
}

void DAGrts(Graph G) {
    int v, time = 0, *pre, *ts;

    pre = (int*) malloc(G->V * sizeof(int));
    ts = (int*) malloc(G->V * sizeof(int));

    for (v = 0; v < G->V; v++) { 
        pre[v] = -1; 
        ts[v] = -1; 
    }
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1) 
            TSdfsR(G, v, ts, pre, &time);

    printf("DAG nodes in reverse topological order \n");
    for (v = 0; v < G->V; v++)
        printf("%s ", STsearchByIndex(G->tab, ts[v]));
    printf("\n");
}