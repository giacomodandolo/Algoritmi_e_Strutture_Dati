#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(FILE* file, int nr, int nc) {
    int **mat, i, j;

    mat = (int**) malloc(nr*sizeof(int*));
    for (i = 0; i < nr; i++) {
        mat[i] = (int*) malloc(nc*sizeof(int));
        for (j = 0; j < nc; j++)
            fscanf(file, "%d", &mat[i][j]);
    }
    return mat;
}

void free2d(int **mat, int nr, int nc) {
    int i;

    for (i = 0; i < nr; i++)
        free(mat[i]);
    free(mat);
}

int *malloc1dR(int dim) {
    int *vett;

    vett = (int*) malloc(dim*sizeof(int));
    return vett;
}

void free1d(int *vett, int dim) {
    free(vett);
}

void separa(int **mat, int nr, int nc, int *vettB, int dimB, int *vettN, int dimN) {
    int i, j, posB = 0, posN = 0, is_black;

    for (i = 0; i < nr; i++)
        for (j = 0; j < nc; j++) {
            is_black = (i+j)%2;
            if (is_black) {
                vettB[posB] = mat[i][j];
                posB++;
            } else {
                vettN[posN] = mat[i][j];
                posN++;
            }
        }
}

void print1d(int *vett, int dim) {
    int i;

    for (i = 0; i < dim; i++)
        printf("%d ", vett[i]);
    printf("\n");
}

int main(void) {
    int nr, nc, **mat, dimB, *vettB, dimN, *vettN;
    char *filename;
    FILE *file;

    printf("Nome file: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    fscanf(file, "%d %d", &nr, &nc);
    mat = malloc2dR(file, nr, nc);

    // printf("nr: %d, nc: %d", nr, nc);
    dimB = dimN = (nr*nc)/2;
    if (nr%2 && nc%2)
        dimB++;
    vettB = malloc1dR(dimB);
    vettN = malloc1dR(dimN);

    separa(mat, nr, nc, vettB, dimB, vettN, dimN);

    print1d(vettN, dimN);
    print1d(vettB, dimB);

    free1d(vettN, dimN);
    free1d(vettB, dimB);
    free2d(mat, nr, nc);
    fclose(file);
    return 0;
}