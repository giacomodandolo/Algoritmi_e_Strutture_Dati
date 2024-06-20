#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 100
#define MAXDIAG 3
#define MAXELEMENTS 5

typedef enum tipologia_t {transizione, indietro, avanti} tipologia;
typedef enum direzione_t {spalle, frontale} direzione;
typedef enum precedenza_t {preceduto, non_preceduto} precedenza;
typedef enum finale_t {seguito, non_seguito} finale;

typedef enum bool_t {false, true} bool;

typedef struct elemento_s {
    char nome[MAXCHAR];
    tipologia tipo;
    direzione dir_ing, dir_usc;
    precedenza req_pre;
    finale fin;
    int diff;
    float val;
} elemento_t;

typedef struct programma_s {
    int index_diag[MAXDIAG][MAXELEMENTS];
    int diff_diag[MAXDIAG], diff;
    bool bonus;
    float val_diag[MAXDIAG], val;
} programma_t;

int prog_check(programma_t* prog, elemento_t* el, int DD, int DP) {
    int i, j;
    bool acr = false, acr_av = false, acr_ind = false, acr_due = false;

    for(i = 0; i < MAXDIAG; i++) {
        acr = false;

        for(j = 0; j < MAXELEMENTS; j++) {
            if(prog->index_diag[i][j] != -1) {
                if(el[prog->index_diag[i][j]].tipo != transizione) {
                    acr = true;
                    if(el[prog->index_diag[i][j]].tipo == indietro)
                        acr_av = true;
                    if(el[prog->index_diag[i][j]].tipo == avanti)
                        acr_ind = true;
                    if(prog->index_diag[i][j+1] != -1 && (el[prog->index_diag[i][j+1]].tipo == avanti || el[prog->index_diag[i][j+1]].tipo == indietro))
                        acr_due = true;
                }
            }
        }
        if(!acr)
            return 0;
    }
    if(!acr || !acr_av || !acr_ind || !acr_due)
        return 0;
    return 1;
}

int main() {
    FILE* f;
    int N, i, j, *pos, DD, DP;
    elemento_t* el;
    programma_t *prog, *sol;

    if((f = fopen("elementi.txt", "r")) == NULL)
        return 1;
    
    fscanf(f, "%d", &N);
    el = (elemento_t*) malloc(N*sizeof(elemento_t));

    for(i = 0; i < N; i++) {
        fscanf(f, "%s %d %d %d %d %d %f %d",
                el[i].nome, &(el[i].tipo), &(el[i].dir_ing), &(el[i].dir_usc), &(el[i].req_pre), &(el[i].fin), &(el[i].val), &(el[i].diff));
    }

    fclose(f);

    prog = (programma_t*) calloc(1, sizeof(programma_t));
    for(i = 0; i < MAXDIAG; i++)
        for(j = 0; j < MAXELEMENTS; j++) {
            prog->index_diag[i][j] = -1;
        }
    
    sol = (programma_t*) calloc(1, sizeof(programma_t));

    printf("DD: ");
    scanf("%d", &DD);
    printf("DP: ");
    scanf("%d", &DP);

    disp_rip(pos, prog, 0, el, N, DD, DP, &sol);

    printf("DD = %d DP = %d\nTOT = %.3f\n", DD, DP, sol->val);
    for(i = 0; i < MAXDIAG; i++) {
        printf("DIAG #%d > %.3f\n", i+1, sol->val_diag[i]);
        for(j = 0; j < MAXELEMENTS && sol->index_diag[i][j] != -1; j++)
            printf("%s ", el[sol->index_diag[i][j]]);
        printf("\n");
    }

    return 0;
}