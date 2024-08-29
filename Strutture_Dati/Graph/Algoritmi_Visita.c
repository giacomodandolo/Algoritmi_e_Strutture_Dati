#include "Algoritmi_Visita.h"

/*
    --- VISITA IN PROFONDITA' ---
    Dato un grafo, a partire da un vertice s, visita tutti i vertici del grafo.
*/

/* 
    --- BASE ---

    Espande l'ultimo vertice scoperto che ha ancora vertici non scoperti adiacenti.
    La scoperta è definita come la prima volta che un vertice si incontra nella visita.
    Il vettore pre contiene i tempi crescenti di scoperta.

    GRAPHsimpleDfs: a partire da un vertice dato visita tutti i vertici di un grafo,
                    richiamando la procedura ricorsiva SimpleDfsR. Termina quando tutti
                    i vertici sono stati visitati.
    
    SimpleDfsR:     visita in profondità a partire da un vertice id identificato con un
                    arco fittizio EDGEcreate(id, id) utile in fase di visualizzazione.
                    Termina quando ha visitato in profondità tutti i nodi raggiungibili
                    da id. 
    
    Notare che il grafo è non pesato come lista delle adiacenze, e si utilizza il contatore
    cnt per i tempi di scoperta.
*/
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

/* 
    --- ESTESA ---

    I nodi sono etichettati con tempo di scoperta e tempo di completamento (ts/tc) e
    viene generata la foresta di alberi della visita in profondità, memorizzata in un
    vettore. Alla fine dell'elaborazione del vertice si aggiorna il vettore post[i].
    Quando è effettuata una scoperta o un completamento, il tempo discreto avanza mediante
    contatore time. Il padre nella visita in profondità è identificato dal vettore st[i].

    GRAPHextendedDfs:   a partire da un vertice dato visita tutti i vertici di un grafo,
                        richiamando la procedura ricorsiva ExtendedDfsR. Termina quando
                        tutti i vertici sono stati visitati.
    
    ExtendedDfsR:       visita in profondità a partire da un vertice id identificato con
                        un arco fittizio EDGEcreate(id, id) utile in fase di visualizzazione.
                        Termina quando ha visitato in profondità tutti i nodi raggiungibili
                        da id.
*/
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

/* 
    --- COMPLETA ---

    Si etichetta ogni arco:
        ORIENTATI
            T (tree)
            B (backward)
            F (forward)
            C (cross)
        NON ORIENTATI
            T (tree)
            B (backward)

    T = archi dell'albero della visita in profondità.

    B = connettono un vertice w ad un suo antenato v nell'albero, dove il tempo di 
        fine elaborazione di v sarà maggiore del tempo di fine elaborazione di w.
        Equivale a testare se, quando scopro l'arco (w, v), post[v] == -1.
            post[v] > post[w]

    F = connettono un vertice w ad un suo discendente v nell'albero, dove il tempo
        di scoperta di v è maggiore del tempo di scoperta di w quando scopro l'arco
        (w, v).
            pre[v] > pre[w]

    C = archi rimanenti, per cui il tempo di scoperta di w è maggiore del tempo di
        scoperta di v quando scopro l'arco (w, v).
            pre[w] > pre[v]

    GRAPHdfs:   a partire da un vertice dato visita tutti i vertici di un grafo,
                richiamando la procedura ricorsiva dfsR. Termina quando tutti i
                vertici sono stati visitati.

    dfsR:       visita in profondità a partire da un vertice id identificato con
                un arco fittizio EDGEcreate(id, id) utile in fase di visualizzazione.
                Termina quando ha visitato in profondità tutti i nodi raggiungibili da id.

*/
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

/* 
    --- VISITA IN AMPIEZZA ---
    A partire da si determinano tutti i vertici raggiungibili da s, si calcola la distanza 
    minima da s di tutti i vertici da esso raggiungibili. Inoltre, genera un albero della 
    visita in ampiezza. In ampiezza si espande tutta la frontiera tra vertici già scoperti 
    e non ancora scoperti.

    --- PRINCIPI BASE ---
    La scoperta di un vertice avviene la prima volta che si incontra nella visita
    raggiungendolo percorrendo un arco. Il vettore pre registra il tempo di scoperta
    di v. Dato un vertice v, il vettore st registra il padre di v nell'albero della
    visita in ampiezza. Non appena il vertice viene scoperto, si registra il tempo di 
    scoperta e il padre nell'albero, concludendo così l'elaborazione del vertice stesso.

    Notare che il grafo è non pesato e utilizza la matrice delle adiacenze, inoltre si
    usa la coda Q di archi, il vettore st definisce i padri nell'albero di visita in
    ampiezza, il vettore pre definisce i tempi di scoperta dei vertici e il contatore 
    time del tempo.

    GRAPHbfs:   a partire da un vertice dato visita tutti i vertici di un grafo,
                richiamando la procedura ricorsiva bfs. Termina quando tutti i
                vertici sono stati visitati.

    bfs:        visita in ampiezza a partire da un vertice di partenza id.
*/
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