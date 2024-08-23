#include <stdio.h>
#include <stdlib.h>
#define STONES 4
#define MAX_FILE 50

typedef enum {
    z, r, t, s
} stone;

int **readStones(FILE* file, int *tests) {
    int **mat, i;

    fscanf(file, "%d", tests);
    mat = (int**) malloc(*tests * sizeof(int*));
    for (i = 0; i < *tests; i++) {
        mat[i] = (int*) malloc(STONES*sizeof(int));
        fscanf(file, "%d %d %d %d", &(mat[i][z]), &(mat[i][r]), &(mat[i][t]), &(mat[i][s]));
    }

    return mat;
}

int check(int *sol, int n) {
    int i;

    for (i = 1; i < n; i++) {
        if (sol[i-1] == z || sol[i-1] == t)
            if (sol[i] != z && sol[i] != r)
                return 0;
        if (sol[i-1] == s || sol[i-1] == r)
            if (sol[i] != s && sol[i] != t)
                return 0;
    }

    return 1;
}

void *copy_sol(int *sol, int n, int *new_sol) {
    int i;
    
    for (i = 0; i < n; i++)
        new_sol[i] = sol[i];
}

void print_sol(int *sol, int n) {
    int i;

    printf("Lunghezza = %d\n", n);
    for (i = 0; i < n; i++)
        printf("%d ", sol[i]);
    printf("\n");
}

void disp_rip(int pos, int *val, int *sol, int n, int *max_sol, int *max_len) {
    int i, is_zt, is_sr;

    if (pos > 0 && check(sol, pos)) {
        if (pos > *max_len) {
            *max_len = pos;
            copy_sol(sol, pos, max_sol);
        }
    }

    for (i = 0; i < n; i++) {
        if (val[i] != 0) {
            sol[pos] = i;
            val[i]--;
            disp_rip(pos+1, val, sol, n, max_sol, max_len);
            val[i]++;
        }
    }
}

int main(void) {
    int i, *sol, dim, *max_sol, max_len, **tests, num_tests;
    char filename[MAX_FILE];
    FILE *file;

    printf("Nome file: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    tests = readStones(file, &num_tests);
    fclose(file);

    for (i = 0; i < num_tests; i++) {
        dim = tests[i][z] + tests[i][r] + tests[i][s] + tests[i][t];
        sol = (int*) malloc(dim*sizeof(int));
        max_sol = (int*) malloc(dim*sizeof(int));
        max_len = 0;
        disp_rip(0, tests[i], sol, STONES, max_sol, &max_len);
        printf("Test #%d\n", i+1);
        print_sol(max_sol, max_len);
        printf("\n");
    }

    return 0;
}