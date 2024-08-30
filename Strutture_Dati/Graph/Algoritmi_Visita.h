#ifndef ALGORITMI_VISITA_H
#define ALGORITMI_VISITA_H

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
void GRAPHsimpleDfs(Graph G, int id);

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
void GRAPHextendedDfs(Graph G, int id);

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
void GRAPHdfs(Graph G, int id);

/* 
    --- VISITA IN AMPIEZZA ---
    A partire da un vertice s si determinano tutti i vertici raggiungibili da s, si calcola 
    la distanza minima da s di tutti i vertici da esso raggiungibili. Inoltre, genera un 
    albero della visita in ampiezza. In ampiezza si espande tutta la frontiera tra vertici 
    già scoperti e non ancora scoperti.

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
void GRAPHbfs(Graph G, int id);

#endif