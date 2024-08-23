#include <stdio.h>
#include <stdlib.h>
#define MAX_FILE 50

typedef struct att {
    int s, f;
} Att;

int check(Att *v, int *sol, int N) {
    int i, j, is_sol, is_not_valid;

    for (i = 0; i < N-1; i++)
        for (j = i+1; j < N; j++) {
            is_sol = sol[i] == 1 && sol[j] == 1;
            is_not_valid = v[i].s < v[j].f && v[j].s < v[i].f;
            if (is_sol && is_not_valid)
                return 0;
        }
    return 1;
}

void printSol(Att *v, int *sol, int N, int d) {
    int i;
    
    printf("Durata: %d\nSol = { ", d);
    for (i = 0; i < N; i++)
        if (sol[i] == 1)
            printf("(%d, %d) ", v[i].s, v[i].f);
    printf("}\n");
}

void attSel_r(int pos, Att *v, int *sol, int N, int *max_sol, int *max_d, int d) {
    int i, new_d;

    if (pos >= N) {
        if (check(v, sol, N))
            if (*max_d < d) {
                *max_d = d;
                for (i = 0; i < N; i++)
                    max_sol[i] = sol[i];
            }
    }

    for (i = pos; i < N; i++) {
        sol[pos] = 0;
        attSel_r(pos+1, v, sol, N, max_sol, max_d, d);
        sol[pos] = 1;
        new_d = d + v[pos].f - v[pos].s;
        attSel_r(pos+1, v, sol, N, max_sol, max_d, new_d);
    }
}

void attSel(int N, Att *v) {
    int d;
    int *sol, *max_sol;

    sol = (int*) malloc(N*sizeof(int));
    max_sol = (int*) malloc(N*sizeof(int));
    d = 0;
    attSel_r(0, v, sol, N, max_sol, &d, 0);
    printSol(v, max_sol, N, d);
}

int main(void) {
    int N, i;
    char filename[MAX_FILE];
    Att *v;
    FILE *file;

    printf("Nome file: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    fscanf(file, "%d", &N);
    v = (Att*) malloc(N*sizeof(Att));
    for (i = 0; i < N; i++)
        fscanf(file, "%d %d", &v[i].s, &v[i].f);

    fclose(file);
    
    attSel(N, v);

    return 0;
}