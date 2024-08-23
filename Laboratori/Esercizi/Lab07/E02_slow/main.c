#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME 100
#define MAX_FILE 50
#define NUM_PARAM 2
#define MAX_DIAG 3
#define MAX_ELEM 5
#define NUM_FLAGS 5
#define MAX_DIFF 8
#define MULT_SCORE 1.5

typedef struct {
    char nome[MAX_NAME];
    int tipo, dir_ing, dir_usc, req_pre, fin;
    float score;
    int diff;
} element;

typedef enum {
    DD, DP
} param;

typedef enum {
    AC, AC_AVA, AC_IND, DA
} flag;

element *readElements(FILE *file, int *n) {
    int i;
    element* new;

    fscanf(file, "%d", n);
    new = (element*) malloc(*n * sizeof(element));
    for (i = 0; i < *n; i++)
        fscanf(file, "%s %d %d %d %d %d %f %d", 
                new[i].nome, &new[i].tipo, &new[i].dir_ing, &new[i].dir_usc, &new[i].req_pre, &new[i].fin, &new[i].score, &new[i].diff);

    return new;
}

int **readTests(FILE *file, int *n) {
    int i, **tests;

    fscanf(file, "%d", n);
    tests = (int**) malloc(*n*sizeof(int*));
    for (i = 0; i < *n; i++) {
        tests[i] = (int*) malloc(NUM_PARAM*sizeof(int));
        fscanf(file, "%d %d", &tests[i][DD], &tests[i][DP]);
    }

    return tests;
}

int **initSol() {
    int i, j, **sol;

    sol = (int**) malloc(MAX_DIAG*sizeof(int*));
    for (i = 0; i < MAX_DIAG; i++) {
        sol[i] = (int*) malloc(MAX_ELEM*sizeof(int));
        for (j = 0; j < MAX_ELEM; j++)
            sol[i][j] = -1;
    }

    return sol;
}

int **updateSol(int **sol) {
    int i, j, **new;

    new = (int**) malloc(MAX_DIAG*sizeof(int*));
    for (i = 0; i < MAX_DIAG; i++) {
        new[i] = (int*) malloc(MAX_ELEM*sizeof(int*));
        for (j = 0; j < MAX_ELEM; j++)
            new[i][j] = sol[i][j];
    }

    return new;
}

void printSol(element *elements, int **sol) {
    int i, j;

    for (i = 0; i < MAX_DIAG; i++) {
        printf("DIAG #%d\n", i);
        for (j = 0; j < MAX_ELEM; j++) {
            if (sol[i][j] != -1)
                printf("%s ", elements[sol[i][j]].nome);
            printf("\n");
        }
        printf("\n");
    }
}

float getScore(element *elements, int **sol) {
    int i, j, last_diff;
    float new, last_score;

    last_score = 0;
    for (i = 0; i < MAX_DIAG; i++)
        for (j = 0; j < MAX_ELEM; j++)
            if (sol[i][j] != -1) {
                if (i == MAX_DIAG-1) {
                    last_diff = elements[sol[i][j]].diff;
                    last_score += elements[sol[i][j]].score;
                } else {
                    new += elements[sol[i][j]].score;
                }
            }
    
    if (last_diff >= MAX_DIFF)
        last_score *= (float) MULT_SCORE;
    new += last_score;

    return new;
}

int checkSol(int **sol, element *elements, int *limit) {
    int i, j, diag_diff, prog_diff, is_double, *flags;
    element prev, curr;

    // printSol(elements, sol);

    flags = (int*) calloc(NUM_FLAGS, sizeof(int));
    for (i = 0; i < MAX_DIAG; i++) {
        prog_diff = 0;
        for (j = 0; j < MAX_ELEM; j++) {
            diag_diff = 0;
            if (sol[i][j] != -1) {
                if (j > 0)
                    prev = elements[sol[i][j-1]];
                curr = elements[sol[i][j]];
                diag_diff += curr.diff;
                prog_diff += curr.diff;
                is_double = (j > 0) && (curr.tipo == 1 || curr.tipo == 2) && (prev.tipo == 1 || prev.tipo == 2);
                if (diag_diff > limit[DD] || prog_diff > limit[DP])
                    return 0;
                if (curr.tipo == 1 || curr.tipo == 2)
                    flags[AC] = 1;
                if (curr.tipo == 1)
                    flags[AC_AVA] = 1;
                if (curr.tipo == 2)
                    flags[AC_IND] = 1;
                if (is_double)
                    flags[DA] = 1;
            } else break;
        }
    }

    for (i = 0; i < NUM_FLAGS; i++)
        if(flags[i] == 0)
            return 0;
    
    return 1;
}

float getHighestScore(int pos, int curr_diag, element *elements, int num_elem, int **sol, int **high_sol, int *limit, float high_score) {
    int i;
    float new_score;

    if (pos >= MAX_ELEM) {
        high_score = getHighestScore(0, curr_diag+1, elements, num_elem, sol, high_sol, limit, high_score);
        return high_score;
    }

    if (curr_diag >= MAX_DIAG) {
        if (checkSol(sol, elements, limit)) {
            new_score = getScore(elements, sol);
            if (new_score > high_score) {
                high_sol = updateSol(sol);
                high_score = new_score;
                return high_score;
            }
        }
    }

    for (i = 0; i < num_elem; i++) {
        if (pos == 0)
            if (elements[i].req_pre != 0)
                continue;
        if (pos > 0) {
            if (elements[sol[curr_diag][pos-1]].dir_ing != elements[i].dir_usc)
                continue;
            if (elements[sol[curr_diag][pos-1]].fin == 1) {
                high_score = getHighestScore(0, curr_diag+1, elements, num_elem, sol, high_sol, limit, high_score);
                break;
            }
        }
        if (curr_diag >= MAX_DIAG)
            break;

        sol[curr_diag][pos] = i;
        high_score = getHighestScore(pos+1, curr_diag, elements, num_elem, sol, high_sol, limit, high_score);
        high_score = getHighestScore(0, curr_diag+1, elements, num_elem, sol, high_sol, limit, high_score);
        sol[curr_diag][pos] = -1;
        high_score = getHighestScore(pos+1, curr_diag, elements, num_elem, sol, high_sol, limit, high_score);
        high_score = getHighestScore(0, curr_diag+1, elements, num_elem, sol, high_sol, limit, high_score);
    }
    
    return high_score;
}

int main(void) {
    int i, n, **tests, num_tests, **sol, **high_sol;
    float max_score;
    char filename[MAX_FILE];
    element *elements;
    FILE *file;

    printf("Nome file (elementi): ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    elements = readElements(file, &n);
    fclose(file);

    printf("Nome file (testset): ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    tests = readTests(file, &num_tests);
    fclose(file);

    sol = initSol();
    high_sol = initSol();
    max_score = 0;

    for (i = 0; i < num_tests; i++) { 
        max_score = getHighestScore(0, 0, elements, n, sol, high_sol, tests[i], max_score);
        printf("TEST #%d\n", i+1);
        printf("DD = %d | DP = %d\n", tests[i][DD], tests[i][DP]);
        printf("TOT = %f\n", max_score);
        printSol(elements, high_sol);
    }

    return 0;
}
