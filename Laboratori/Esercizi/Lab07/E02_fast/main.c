#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_NAME 100
#define MAX_FILE 50
#define MAX_DIAG 3
#define MAX_ELEM 5
#define MAX_DIFF 8
#define NUM_PARAM 2

typedef enum Tipo {
    transizione, avanti, indietro
} tipo;

typedef enum Direzione {
    spalle, frontale
} direzione;

typedef enum Precedenza {
    no_prec, prec
} precedenza;

typedef enum Finale {
    seguito, non_seguito
} finale;

typedef enum Param {
    DD, DP
} param;

typedef struct Element {
    char nome[MAX_NAME];
    int tipo, dir_ing, dir_usc, req_pred, fin, diff;
    float val;
} element;

typedef struct Diagonal {
    int elem_index[MAX_ELEM], n, tot_diff;
    float tot_val;
} diagonal;

element *readElements(FILE *file, int *n) {
    int i;
    element* new;

    fscanf(file, "%d", n);
    new = (element*) malloc(*n * sizeof(element));
    for (i = 0; i < *n; i++)
        fscanf(file, "%s %d %d %d %d %d %f %d", 
            new[i].nome, &new[i].tipo, &new[i].dir_ing, &new[i].dir_usc, &new[i].req_pred, &new[i].fin, &new[i].val, &new[i].diff);

    return new;
}

int **readTests(FILE *file, int *n) {
    int i, **tests;

    fscanf(file, "%d", n);
    tests = (int**) malloc(*n * sizeof(int*));
    for (i = 0; i < *n; i++) {
        tests[i] = (int*) malloc(NUM_PARAM*sizeof(int));
        fscanf(file, "%d %d", &tests[i][DD], &tests[i][DP]);
    }

    return tests;
}

diagonal *copySol(diagonal *sol, int n) {
    int i;
    diagonal *new;

    new = (diagonal*) malloc(n*sizeof(diagonal));
    for (i = 0; i < n; i++)
        new->elem_index[i] = sol->elem_index[i];
    
    new->n = sol->n;
    new->tot_diff = sol->tot_diff;
    new->tot_val = sol->tot_val;

    return new;
}

void printSol(element *elements, diagonal **sol, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        if (i == n-1 && sol[i]->tot_diff > MAX_DIFF)
            printf("Diag #%d > %.3f * 1.5 (BONUS) \n", i+1, sol[i]->tot_val);
        else
            printf("Diag #%d > %.3f\n", i+1, sol[i]->tot_val);
        for (j = 0; j < sol[i]->n; j++)
            printf("%s ", elements[sol[i]->elem_index[j]].nome);
        printf("\n\n");
    }
}

int isValid(element* elements, diagonal *sol, int pos) {
    int i;

    for (i = 0; i < pos; i++)
        if (elements[sol->elem_index[i]].tipo == avanti || elements[sol->elem_index[i]].tipo == indietro)
            return 1;
    
    return 0;
}

int isDiagonalValid(element* elements, diagonal *sol, int pos, int i, int pDD) {
    if (pos == 0) {
        if (elements[i].req_pred == no_prec 
            && elements[i].dir_ing == frontale && elements[i].diff <= pDD)
            return 1;
        return 0;
    }

    if (elements[sol->elem_index[pos-1]].fin == seguito 
        && elements[sol->elem_index[pos-1]].dir_usc == elements[i].dir_ing
        && (elements[i].diff + sol->tot_diff) <= pDD)
        return 1;
    
    return 0;
}

int dispRip(int pos, element *elements, diagonal *sol, diagonal **all_sol, int n, int *max_n, int k, int pDD, int cnt) {
    int i;

    if (isValid(elements, sol, pos)) {
        sol->n = pos;
        all_sol[cnt] = copySol(sol, pos);
        cnt++;
    }

    if (pos >= k)
        return cnt;

    for (i = 0; i < n; i++) {
        if (isDiagonalValid(elements, sol, pos, i, pDD)) {
            sol->elem_index[pos] = i;
            sol->tot_diff += elements[i].diff;
            sol->tot_val += elements[i].val;

            cnt = dispRip(pos+1, elements, sol, all_sol, n, max_n, k, pDD, cnt);
            
            sol->tot_diff -= elements[i].diff;
            sol->tot_val -= elements[i].val;
        }
    }
    return cnt;
}

int isValidProg(element *elements, diagonal **sol, int n, int pDP) {
    int i, j, totalDiff, checkDA, checkAVA, checkIND;

    totalDiff = checkDA = checkAVA = checkIND = 0;

    for (i = 0; i < n; i++)
        totalDiff += sol[i]->tot_diff;

    if (totalDiff > pDP)
        return 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < sol[i]->n; j++) {
            if (elements[sol[i]->elem_index[j]].tipo != transizione) {
                if (elements[sol[i]->elem_index[j]].tipo == avanti)
                    checkAVA = 1;
                else
                    checkIND = 1;

                if ((j < (sol[i]->n - 1)) 
                    && elements[sol[i]->elem_index[j+1]].tipo != transizione)
                    checkDA = 1;

                if(checkAVA == 1 && checkIND == 1 && checkDA == 1)
                    return 1;
            }
        }
    }

    return 0;
}

float getScore(element *elements, diagonal **sol, int n) {
    int i;
    float score;

    score = 0;
    for (i = 0; i < n-1; i++)
        score += sol[i]->tot_val;

    if (elements[sol[n-1]->elem_index[sol[n-1]->n - 1]].diff >= MAX_DIFF)
        score += sol[n-1]->tot_val * 1.5;
    else
        score += sol[n-1]->tot_val;
    
    return score;
}

float getHighestScore(int pos, element *elements, diagonal **sol, diagonal **diags, diagonal **best_sol, int num_diags, int k, int pDP, float high_score) {
    int i; 
    float new_score;

    if (pos == k) {
        if (isValidProg(elements, sol, pos, pDP)) {
            new_score = getScore(elements, sol, k);
            
            if (new_score > high_score) {
                high_score = new_score;
                for (i = 0; i < k; i++)
                    best_sol[i] = sol[i];
            }
        }
        return high_score;
    }

    for (i = 0; i < num_diags; i++) {
        sol[pos] = diags[i];
        high_score = getHighestScore(pos+1, elements, sol, diags, best_sol, num_diags, k, pDP, high_score);
    }

    return high_score;
}

float getHighestProgram(element *elements, diagonal **best_sol, int n, int pDD, int pDP) {
    int num_diags, max_diags;
    float high_score;
    diagonal **diags, *sol, **sol_second;

    max_diags = pow(n, MAX_ELEM);
    sol = (diagonal*) malloc(MAX_DIAG*sizeof(diagonal));
    sol->n = 0;
    sol->tot_diff = 0;
    sol->tot_val = 0;
    diags = (diagonal**) malloc(max_diags * sizeof(diagonal*));
    num_diags = dispRip(0, elements, sol, diags, n, &max_diags, MAX_ELEM, pDD, 0);

    printf("MAX_DIAGS = %d\nNUM_DIAGS = %d\n\n", max_diags, num_diags);

    sol_second = (diagonal**) malloc(MAX_DIAG*sizeof(diagonal*));
    high_score = getHighestScore(0, elements, sol_second, diags, best_sol, num_diags, MAX_DIAG, pDP, 0);

    free(diags);
    free(sol);
    free(sol_second);

    return high_score;
}

int main(void) {
    int i, n, **tests, num_tests;
    float max_score;
    char filename[MAX_FILE];
    element *elements;
    diagonal **best_sol;
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
    
    for (i = 0; i < num_tests; i++) {
        best_sol = (diagonal**) malloc(MAX_DIAG*sizeof(diagonal*));
        printf("------------\n");
        printf("TEST #%d\n", i+1);
        max_score = getHighestProgram(elements, best_sol, n, tests[i][DD], tests[i][DP]);
        printf("DD = %d | DP = %d\n", tests[i][DD], tests[i][DP]);
        printf("TOT = %.3f\n\n", max_score);
        printSol(elements, best_sol, MAX_DIAG);
        free(best_sol);
    }

    return 0;
}