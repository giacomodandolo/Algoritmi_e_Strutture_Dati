#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge { 
    int v; 
    int w; 
    int wt; 
} Edge;
typedef struct graph *Graph;

/* INIZIALIZZAZIONE */
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHload(FILE *fin);

/* VISUALIZZAZIONE */
void GRAPHstore(Graph G, FILE *fout);
void GRAPHedges(Graph G, Edge *a);

/* OTTIENI INDICE */
int GRAPHgetIndex(Graph G, char *label);

/* INSERIMENTO ARCHI */
void GRAPHinsertE(Graph G, int id1, int id2, int wt);

/* RIMOZIONE ARCHI */
void GRAPHremoveE(Graph G, int id1, int id2);

/*
    --- CAMMINI ---

    Il cammino di Hamilton tra v e w procede come segue:
    1)  per ogni vertice t adiacente al vertice corrente v,
        determinare ricorsivamente se esiste un cammino
        semplice da t a w;
    2)  ritorno con successo se e solo se la lunghezza del
        cammino è |V|-1;
    3)  set della cella dell'array visited per marcare i nodi
        già visitati;
    4)  reset della cella dell'array visited quando ritorna
        con insuccesso.
*/
void GRAPHpath(Graph G, int id1, int id2);
void GRAPHpathH(Graph G, int id1, int id2);

/* 
    --- VISITA --- 

    Vedi "Algoritmi_Visita.h".
*/
void GRAPHbfs(Graph G, int id);
void GRAPHdfs(Graph G, int id);

/* 
    --- COMPONENTI FORTEMENTE CONNESSE ---

    L'algoritmo di Kosaraju dice di:
    1)  trasporre il grafo;
    2)  eseguire DFS sul grafo trasporto, calcolando
        i tempi di scoperta e fine elaborazione;
    3)  eseguire DFS sul grafo originale per tempi di fine
        elaborazione decrescenti;
    4)  gli alberi dell'ultima DFS sono le componenti
        fortemente connesse.
*/
int GRAPHscc(Graph G);
Graph GRAPHreverse(Graph G);

/* ALBERI RICOPRENTI MINIMI */
void GRAPHmstK(Graph G);
void GRAPHmstP(Graph G);

/* 
    --- CAMMINO MINIMO ---

    Il rilassamento è lasciare che una soluzione violi un
    vincolo temporaneamente e poi eliminare la violazione, e
    avviene verificando se conviene il cammino da s a u.

    L'algoritmo di Djikstra e l'algoritmo di Bellman-Ford
    sono definiti per sorgente singola, con il cammino minimo
    e il suo peso da s a ogni altro vertice v.
    
    I cammini minimi non possono contenere cicli a peso positivo
    o a peso negativo.
*/

/* 
    --- ALGORITMO DI DJIKSTRA ---

    L'algoritmo di Djikstra non garantisce una soluzione ottima.
    Inoltre, se è presente un ciclo con peso negativo, il risultato
    è senza significato.

    Si utilizza una strategia greedy, nella quale si definisce
    l'insieme dei vertici il cui peso sul cammino minimo da s
    è già stato determinato, e definiamo V-S come la coda a
    priorità dei vertici ancora da stimare. Termina quando la coda
    a priorità è vuota.

    Il procedimento è come segue:
    1)  estrae u da V-S;
    2)  inserisce u in S;
    3)  rilassa tutti gli archi uscenti da u.
*/
void GRAPHspD(Graph G, int id);

/* 
    --- ALGORITMO DI BELLMAN-FORD ---

    L'algoritmo di Bellman-Ford garantisce una soluzione ottima.
    Inoltre, se è presente un ciclo con peso negativo esso è rilevato.

    Si utilizza la programmazione dinamica, nella quale la soluzione
    ricorsiva è la lunghezza del cammino minimo da s a v con al più
    w archi, dove d0 vale 0 se v coincide con s, infinito altrimenti.
    Con metodologia bottom-up:
    -   al passo i-esimo si applica il ciclo di rilassamento sugli
        archi in avanti;
    -   al V-esimo passo, se si diminuisce almeno una stima esiste
        un ciclo di peso negativo, altrimenti si ha soluzione ottima.
*/
void GRAPHspBF(Graph G, int id);

/* ORDINAMENTO TOPOLOGICO (DAG) */
void TSdfsR(Graph G, int v, int *ts, int *pre, int *time);
void DAGrts(Graph G);

#endif