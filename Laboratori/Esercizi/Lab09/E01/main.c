#include "Graph.h"
#define MAX_FILE 30+1

int main(void) {
    char filename[MAX_FILE];
    Graph G;

    while(1) {
        printf("\nNome file: ");
        scanf("%s", filename);
        
        if (strcmp(filename, "exit") == 0)
            break;

        G = GRAPHfile(filename);
        GRAPHprint(G);
    }
    return 0;
}