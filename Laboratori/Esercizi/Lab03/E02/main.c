#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 255+1

void getSongs(FILE *file, int A, int *dim, char ***c) {
    int i, j;
    
    for (i = 0; i < A; i++) {
        fscanf(file, "%d", &dim[i]);
        c[i] = (char**) malloc(dim[i]*sizeof(char*));
        for (j = 0; j < dim[i]; j++) {
            c[i][j] = (char*) malloc(MAX_LENGTH*sizeof(char));
            fscanf(file, "%s", c[i][j]);
        }
    }
}

void printSongs(int A, int cnt, int *sol, char ***c) {
    int i;

    printf("\nPlaylist n.%d\n", cnt+1);
    for (i = 0; i < A; i++) {
        printf("- %s\n", c[i][sol[i]]);
    }
}

int genPlaylists(int pos, int A, int *sol, int* dim, char ***c, int cnt) {
    int i;

    if (pos >= A) {
        printSongs(A, cnt, sol, c);
        return cnt+1;
    }

    for (i = 0; i < dim[pos]; i++) {
        sol[pos] = i;
        cnt = genPlaylists(pos+1, A, sol, dim, c, cnt);
    }
    return cnt;
}

int main(void) {
    int A, *dim, *sol;
    char ***c, filename[50];
    FILE* file;

    printf("Nome file: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    fscanf(file, "%d", &A);

    dim = (int*) malloc(A*sizeof(int));
    c = (char***) malloc(A*sizeof(char**));
    sol = (int*) malloc(A*sizeof(int));

    printf("a");

    getSongs(file, A, dim, c);
    printf("%s", c[0][0]);

    genPlaylists(0, A, sol, dim, c, 0);

    fclose(file);
    return 0;
}