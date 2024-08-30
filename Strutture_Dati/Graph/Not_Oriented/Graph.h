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
int GRAPHpath(Graph G, int id1, int id2);
void GRAPHpathH(Graph G, int id1, int id2);

/* 
    --- VISITA ---
    
    Vedi "Algoritmi_Visita.h".
*/
void GRAPHbfs(Graph G, int id);
void GRAPHdfs(Graph G, int id);

/* 
    --- COMPONENTI CONNESSE ---

    In un grafo non orientato ogni albero della foresta della DFS è
    una componente connessa. Si utilizza un array che memorizza
    interi che identificano ciascuna componente connessa.
*/
int GRAPHcc(Graph G);

#endif