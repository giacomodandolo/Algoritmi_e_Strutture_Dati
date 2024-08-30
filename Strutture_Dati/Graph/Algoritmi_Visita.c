#include "Algoritmi_Visita.h"

static void simpleDfsR(Graph G, Edge e, int *cnt, int *pre) {
    link t; 
    int w = e.w;
    
    pre[w] = (*cnt)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            simpleDfsR(G, EDGEcreate(w, t->v), cnt, pre);
}

void GRAPHsimpleDfs(Graph G, int id) {
    int v, cnt = 0, *pre;
    
    pre = malloc(G->V * sizeof(int));
    if (pre == NULL) 
        return;
    for (v = 0; v < G->V; v++) 
        pre[v] = -1;

    simpleDfsR(G, EDGEcreate(id, id), &cnt, pre);
    
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            simpleDfsR(G, EDGEcreate(v,v), &cnt, pre);
    
    printf("discovery time labels \n");
    for (v = 0; v < G->V; v++)
        printf("vertex %s : %d \n", STsearchByIndex(G->tab, v), pre[v]);
}

static void ExtendedDfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st) {
    link t; 
    int w = e.w;

    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            ExtendedDfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
    post[w] = (*time)++;
}

void GRAPHextendedDfs(Graph G, int id) {
    int v, time = 0, *pre, *post, *st;

    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1; 
        post[v] = -1; 
        st[v] = -1;
    }

    extendedDfsR(G, EDGEcreate(id, id), &time, pre, post, st);
    
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            extendedDfsR(G, EDGEcreate(v, v), &time, pre, post, st);
    
    printf("discovery/endprocessing time labels \n");
    for (v = 0; v < G->V; v++)
        printf("%s:%d/%d\n", STsearchByIndex(G->tab,v), pre[v], post[v]);
    printf("resulting DFS tree \n");
    for (v = 0; v < G->V; v++)
        printf("%s’s parent: %s \n",    STsearchByIndex (G->tab, v),
                                        STsearchByIndex (G->tab, st[v]));
}

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st) {
    link t; 
    int v, w = e.w; 
    Edge x;
    
    if (e.v != e.w)
        printf("(%s, %s):  T \n",   STsearchByIndex(G->tab, e.v), 
                                    STsearchByIndex(G->tab, e.w));
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
        else {
            v = t->v;
            x = EDGEcreate(w, v);
        }
    
    /* Non orientato */
    if (pre[w] < pre[v])
        printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
                                STsearchByIndex(G->tab, x.w));
    
    /* Orientato */
    if (pre[w] < pre[v])
        if (post[v] == -1)
            printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
                                    STsearchByIndex(G->tab, x.w));
        else
            if (pre[v] > pre[w])
                printf("(%s, %s): F\n", STsearchByIndex(G->tab, x.v),
                                        STsearchByIndex(G->tab, x.w));
            else
                printf("(%s, %s): C\n", STsearchByIndex(G->tab, x.v),
                                        STsearchByIndex(G->tab, x.w));
    
    post[w] = (*time)++;
}

void GRAPHdfs(Graph G, int id) {
    int v, time = 0, *pre, *post, *st;

    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) {
        pre[v] = -1; 
        post[v] = -1; 
        st[v] = -1;
    }

    dfsR(G, EDGEcreate(id, id), &time, pre, post, st);
    
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, EDGEcreate(v, v), &time, pre, post, st);
    
    printf("discovery/endprocessing time labels \n");
    for (v = 0; v < G->V; v++)
        printf("%s:%d/%d\n", STsearchByIndex(G->tab,v), pre[v], post[v]);
    printf("resulting DFS tree \n");
    for (v = 0; v < G->V; v++)
        printf("%s’s parent: %s \n",    STsearchByIndex (G->tab, v),
                                        STsearchByIndex (G->tab, st[v]));
}

static void bfs(Graph G, Edge e, int *time, int *pre, int *st, int *dist) {
    int x;
    Q q = Qinit();

    Qput(q, e);
    dist[e.v] = -1;
    while (!Qempty(q))
        if (pre[(e = Qget(q)).w] == -1) {
            pre[e.w] = (*time)++;
            st[e.w] = e.v;
            dist[e.w] = dist[e.v]+1; 
            for (x = 0; x < G->V; x++)
                if (G->madj[e.w][x] == 1)
                    if (pre[x] == -1)
                        Qput(q, EDGEcreate(e.w, x));
        }
}

void GRAPHbfs(Graph G, int id) {
    int v, time=0, *pre, *st, *dist;
    
    pre = (int*) malloc(G->V*sizeof(int));
    st = (int*) malloc(G->V*sizeof(int));
    dist = (int*) malloc(G->V*sizeof(int));

    for (v = 0; v < G->V; v++) {
        pre[v] = -1; 
        st[v] = -1; 
        dist[v] = INT_MAX;
    }

    bfs(G, EDGEcreate(id,id), &time, pre, st, dist);
    
    printf("\n Resulting BFS tree \n");
    for (v = 0; v < G->V; v++)
        if (st[v] != -1)
        printf("%s’s parent is: %s\n",   STsearchByIndex(G->tab, v), 
                                        STsearchByIndex(G->tab, st[v]));
    printf("\n Levelizing \n");
    for (v = 0; v < G->V; v++)
        if (st[v] != -1)
            printf("%s: %d \n", STsearchByIndex(G->tab,v),dist[v]);
}