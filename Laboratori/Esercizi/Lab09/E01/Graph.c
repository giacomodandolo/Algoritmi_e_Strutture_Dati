#include "Graph.h"

typedef struct node_t *link;

typedef struct node_t {
    int v, wt;
    link next;
} node;

typedef struct edge_t {
    int v, w, wt;
} Edge;

typedef struct graph_t {
    int V;
    link *a, z;
    ST tab;
} *Graph;

static Edge *EDGEcreate(int v, int w, int wt) {
    Edge *e;

    e = (Edge*) malloc(sizeof(Edge));
    e->v = v;
    e->w = w;
    e->wt = wt;

    return e;
}

static link NEW(int v, int wt, link next) {
    link x;

    x = (link) malloc(sizeof(node));
    x->v = v;
    x->wt = wt;
    x->next = next;

    return x;
}

static link *LISTinit(int N) {
    link *l;

    l = (link*) malloc(N*sizeof(link));

    return l;
}

static void LISTfree(link h, link z) {
    link x, tmp;

    for (x = h; x != z; ) {
        tmp = x;
        x = x->next;
        free(tmp);
    }
}

static link LISTinsertHead(link h, int v, int wt) {
    h = NEW(v, wt, h);
    
    return h;
}

Graph GRAPHinit(int V) {
    int i;
    Graph G;

    G = (Graph) malloc(sizeof(*G));
    G->V = V;
    G->a = LISTinit(G->V);
    G->z = NEW(-1, -1, NULL);
    for (i = 0; i < G->V; i++)
        G->a[i] = G->z;
    G->tab = STinit(V);

    return G;
}

void GRAPHfree(Graph G) {
    int i;

    for (i = 0; i < G->V; i++)
        LISTfree(G->a[i], G->z);
    free(G->z);
    STfree(G->tab);
    free(G);
}

int GRAPHgetV(Graph G) {
    return G->V;
}

Edge **EDGEvectInit(int V) {
    int i;
    Edge **e;

    e = (Edge**) malloc(V*sizeof(Edge*));
    for (i = 0; i < V; i++)
        e[i] = (Edge*) malloc(V*sizeof(Edge));
    
    return e;
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
        G->a[i] = LISTinsertHead(G->a[i], j, wt);
    }

    return G;
}

void GRAPHprint(Graph G) {
    int i;
    char c, c1, c2;
    link x;

    printf("Numero nodi: %d\n", G->V);
    for (i = 0; i < G->V; i++) {
        c = STsearchByIndex(G->tab, i);
        printf("%d: %c\n", i, c);
    }
    printf("\n");

    printf("Archi: \n");
    for (i = 0; i < G->V; i++)
        for (x = G->a[i]; x != G->z; x = x->next) {
            c1 = STsearchByIndex(G->tab, i);
            c2 = STsearchByIndex(G->tab, x->v);
            printf("(%c, %c): %d\n", c1, c2, x->wt);
        }
}

static void removeE(Graph G, Edge *e) {
    int v = e->v, w = e->w;
    link x;

    if (G->a[v]->v == w)
        G->a[v] = G->a[v]->next;
    else
        for (x = G->a[v]; x != G->z; x = x->next)
            if (x->next->v == w)
                x->next = x->next->next;
}

void GRAPHremoveE(Graph G, int v, int w) {
    removeE(G, EDGEcreate(v, w, 0));
}

static int dfsFindBR(Graph G, Edge *e, int *time, int *pre, int *post, int *st, Edge **B, int *cnt, int *cntT) {
    link t;
    int v, w = e->w;
    Edge *x;

    st[e->w] = e->v;
    pre[w] = (*time)++;
    for (t = G->a[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            *cnt = dfsFindBR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st, B, cnt, cntT);
        else {
            v = t->v;
            x = EDGEcreate(w, v, t->wt);
            if (post[v] == -1) {
                (*B)[*cntT].v = x->v;
                (*B)[*cntT].w = x->w;
                (*B)[*cntT].wt = x->wt;
                *cnt = *cnt + 1;
                *cntT = *cntT + 1;
                // printf("(%c, %c) | wt = %d\n", STsearchByIndex(G->tab, x->v), STsearchByIndex(G->tab, x->w), x->wt);
            }
        }

    post[w] = (*time)++;

    return *cnt;
}

int GRAPHdfsFindB(Graph G, int id, Edge **B, int *cntT) {
    int v, time = 0, *pre, *post, *st, cnt;

    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }

    cnt = 0;
    cnt = dfsFindBR(G, EDGEcreate(id, id, 0), &time, pre, post, st, B, &cnt, cntT);

    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            cnt = dfsFindBR(G, EDGEcreate(v, v, G->a[v]->wt), &time, pre, post, st, B, &cnt, cntT);
    
    return cnt;
}

void EDGEdag(Graph G, Edge **B, int cnt, int cntT) {
    int i, j, k, sumWT, maxWT, tmp;
    
    k = 0;
    for (i = 0; i < (cntT/cnt); i++) {
        sumWT = 0;
        for (j = 0; j < cnt; j++, k++)
            sumWT = sumWT + (*B)[k].wt;
        if (sumWT > maxWT) {
            maxWT = sumWT;
            tmp = i;
        }
    }

    // printf("MAX = (%d, %d) | wt = %d\n", (*B)->v, (*B)->w, (*B)->wt);
    for (i = 0; i < cnt; i++)
        GRAPHremoveE(G, (*B)[tmp+i].v, (*B)[tmp+i].w);
}

static void TSdfsR(Graph G, int v, int *ts, int *pre, int *time) {
    link t; 

    pre[v] = 0;
    for (t = G->a[v]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(G, t->v, ts, pre, time);
    ts[(*time)--] = v;
}

static void DAGlongestPath(Graph G, int *ts, int id, int i) {
    int *d, j, w, v;
    link t;

    v = id;
    d = malloc((G->V)*sizeof(int));
    for (j = 0; j < (G->V); j++) {
        d[j] = -1;
    }
    d[v] = 0;
    for (j = i; j < G->V; j++) {
        w = ts[j];
        if (d[w] == -1) 
            continue;
        for (t = G->a[w]; t != G->z; t = t->next){
            //printf("(%d, %d) | wt = %d\n", w, t->v, t->wt);
            if(d[t->v] == -1 || d[w] + t->wt > d[t->v]) {
                d[t->v] = d[w] + t->wt;
                /*for (v = 0; v < G->V; v++) 
                    printf("Stima %c: %d\n", STsearchByIndex(G->tab, v), d[v]);*/
            }
        }
    }

    for (v = 0; v < G->V; v++)
        printf("%c = %d\n", STsearchByIndex(G->tab, v), d[v]);
    
}

void DAGrts(Graph G) {
    int v, i, time = G->V-1, *pre, *ts;

    pre = (int*) malloc(G->V * sizeof(int));
    ts = (int*) malloc(G->V * sizeof(int));

    for (v = 0; v < G->V; v++) { 
        pre[v] = -1; 
        ts[v] = -1; 
    }
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1) 
            TSdfsR(G, v, ts, pre, &time);

    printf("DAG nodes in topological order = ");
    for (v = 0; v < G->V; v++)
        printf("%c ", STsearchByIndex(G->tab, ts[v]));
    printf("\n\n");

    for (i = 0; i < (G->V); i++) {
        printf("Longest Path %c = \n", STsearchByIndex(G->tab, ts[i]));
        DAGlongestPath(G, ts, ts[i], i);
        printf("\n");
    }
    printf("\n");
}
