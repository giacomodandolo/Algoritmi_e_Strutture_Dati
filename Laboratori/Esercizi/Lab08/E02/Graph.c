#include "Graph.h"

typedef struct node_t {
    int v, wt;
    link next;
} node, *link;

typedef struct graph_t {
    int V, E;
    int is_ladj;
    int **madj;
    link *ladj;
    ST tab;
} *Graph;

int adjacent(Graph G, int i, int j) {
    return G->madj[i][j] != 0;
}

int **MATRIXinit(int r, int c, int v) {
    int i, j, **m;

    m = (int**) malloc(r*sizeof(int*));
    for (i = 0; i < r; i++) {
        m[i] = (int*) malloc(c*sizeof(int));
        for (j = 0; j < c; j++)
            m[i][j] = v;
    }

    return m;
}

void MATRIXfree(int **m, int r) {
    int i;

    for (i = 0; i < r; i++)
        free(m[i]);
    free(m);
}

link LISTnew(int v, int wt, link next) {
    link t;

    t = (link) malloc(sizeof(node));
    t->v = v;
    t->wt = wt;
    t->next = next;

    return t;
}

link LISTinshead(int v, int wt, link h) {
    link t;

    t = LISTnew(v, wt, h);

    return t;
}

link LISTdelhead(link h) {
    link t = h;
    if (h == NULL)
        return NULL;
    h = h->next;
    free(t);
    return h;
}

void LISTfree(link* lists, int n) {
    int i;

    for (i = 0; i < n; i++)
        while (lists[i] != NULL)
            lists[i] = LISTdelhead(lists[i]);
    free(lists);
}

void LISTprint(link h) {
    link x;

    for (x = h; x != NULL; x = x->next)
        printf("ID = %d\nwt = %d\n\n", x->v, x->wt);
}

void LISTprintAll(Graph G) {
    int i;

    for (i = 0; i < G->V; i++)
        if (STsearchByIndex(G->tab, i) != NULL) {
            printf("---- INDEX #%d ----\n", i);
            LISTprint(G->ladj[i]);
        }
}

Graph GRAPHinit(int V) {
    Graph G;

    G = (Graph) malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->madj = MATRIXinit(V, V, 0);
    G->tab = STinit(V);

    return G;
}

void GRAPHfree(Graph G) {
    STfree(G->tab);
    MATRIXfree(G->madj, G->V);
    if (G->is_ladj)
        LISTfree(G->ladj, G->E);
    free(G);
}

void GRAPHinsertE(Graph G, Key v, char *net1, Key w, char *net2, int wt) {
    int i, j;
    Item *item;
    
    i = STsearch(G->tab, v);
    j = STsearch(G->tab, w);
    
    item = ITEMsetvoid();
    if (i == -1) {
        item = ITEMload(item, v, net1);
        STinsert(G->tab, item);    
    }

    item = ITEMsetvoid();
    if (j == -1) {
        item = ITEMload(item, w, net2);
        STinsert(G->tab, item);
    }

    G->madj[STsearch(G->tab, v)][STsearch(G->tab, w)] = wt;
    G->madj[STsearch(G->tab, w)][STsearch(G->tab, v)] = wt;
    G->E = G->E + 1;
}

void GRAPHstore(Graph G) {
    int i, j;

    for (i = 0; i < G->V; i++) {
        if (STsearchByIndex(G->tab, i) != NULL) {
            printf("---- NODE #%d ----\n", i);
            STdisplayByIndex(G->tab, i);
            printf("\n<--- CONNECTS --->\n");
            for (j = 0; j < G->V; j++) {
                if (G->madj[i][j] != 0) {
                    printf("\n");
                    STdisplayByIndex(G->tab, j);
                    printf("wt = %d\n", G->madj[i][j]);
                }
            }
            printf("\n");
        }
    }
}

void GRAPHmat2list(Graph G) {
    int i, j;

    G->ladj = (link*) malloc(G->V*sizeof(link));
    for (i = 0; i < G->V; i++) {
        G->ladj[i] = NULL;
        for (j = 0; j < G->V; j++)
            if (adjacent(G, i, j))
                G->ladj[i] = LISTinshead(j, G->madj[i][j], G->ladj[i]);
    }

    G->is_ladj = 1;
}

int GRAPHcheck3clique(Graph G, Key v, Key w, Key t) {
    int first, v_s, second, w_s, third, t_s;

    v_s = STsearch(G->tab, v);
    w_s = STsearch(G->tab, w);
    t_s = STsearch(G->tab, t);

    if (v_s == -1 || w_s == -1 || t_s == -1)
        return 0;

    first = adjacent(G, v_s, w_s);
    second = adjacent(G, v_s, t_s);
    third = adjacent(G, w_s, t_s);
    return (first && second && third);
}
