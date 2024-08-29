#include "Graph.h"
#define MAX_FILE 30+1

void showMenu() {
    printf("0 > Termina il programma;\n");
    printf("1 > Carica un altro grafo da file;\n");
    printf("2 > Visualizza il grafo;\n");
    printf("3 > Controlla se il grafo e' un DAG;\n");
    printf("4 > Costruzione di un DAG rimuovendo l'insieme di archi a peso massimo;\n");
    printf("5 > Calcolo delle distanze massime da ogni nodo sorgente verso ogni nodo del DAG;\n");
}

int main(void) {
    int i, isDAG, cntB, cntT, scelta;
    char filename[MAX_FILE];
    Edge **B;
    Graph G;

    printf("\nNome file: ");
    scanf("%s", filename);
    G = GRAPHfile(filename);
    isDAG = -1;
    cntT = 0;

    do {
        showMenu();
        printf("\nScelta: ");
        scanf("%d", &scelta);
        printf("\n");
        switch(scelta) {
            case 0:
                printf("Terminando il programma...\n");
                GRAPHfree(G);
                break;
            case 1:
                GRAPHfree(G);
                printf("\nNome file: ");
                scanf("%s", filename);
                G = GRAPHfile(filename);
                isDAG = -1;
                cntT = 0;
                break;
            case 2:
                GRAPHprint(G);
                printf("\n");
                break;
            case 3:
                B = EDGEvectInit(GRAPHgetV(G));
                for (i = 0; i < GRAPHgetV(G); i++) {
                    cntB = GRAPHdfsFindB(G, i, B, &cntT);
                }
                if (!cntB) {
                    printf("Il grafo e' un DAG.\n");
                    isDAG = 1;
                } else {
                    printf("Il grafo non e' un DAG.\n");
                    isDAG = 0;
                }
                printf("\n");
                break;
            case 4:
                if (isDAG == -1) {
                    printf("Non e' verificato se il grafo e' un DAG.\n");
                } else if (!isDAG) {
                    EDGEdag(G, B, cntB, cntT);
                    GRAPHprint(G);
                    printf("\n");
                    isDAG = 1;
                } else
                    printf("Il grafo e' gia' un DAG.\n");
                printf("\n");
                break;
            case 5:
                DAGrts(G);
                break;
            default:
                printf("Inserisci un valore valido.\n");
                break;
        }
    } while(scelta != 0);
    return 0;
}