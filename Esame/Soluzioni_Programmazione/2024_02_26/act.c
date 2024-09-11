#include "act.h"

typedef struct activity { 
    char nome[MAX_LEN];
    int t_i, t_f;
    int val;
    int precedenti[MAX_VINC];
    int prec;
} *Activity;

typedef struct activities {
    int NA, NP;
    Activity *a;
} *ACT;

static Activity ACTIVITYfile(FILE *file) {
    Activity att;
    char nome[MAX_LEN];
    int t_i, t_f, val;

    att = (Activity) malloc(sizeof(*att));
    
    fscanf(file, "%s %d %d %d", nome, t_i, t_f, val);
    
    strcpy(att->nome, nome);
    att->t_i = t_i;
    att->t_f = t_f;
    att->val = val;

    return att;
}

static int ACTIVITYindex(ACT atts, char *s) {
    int i;

    for (i = 0; i < atts->NA; i++)
        if (strcmp(atts->a[i], s) == 0)
            return i;
    
    return -1;
}

static ACT ACTIVITYfileVincoli(FILE *file, ACT atts) {
    int i, j, index;
    char s[MAX_LEN];

    fscanf(file, "%s", s);
    index = ACTIVITYindex(atts, s);

    if (index == -1)
        return NULL;

    i = 0;
    while (fscanf(file, "%s", s) == 1) {
        j = ACTIVITYindex(atts, s);
        atts->a[index]->precedenti[i] = j;
        i++;
    }

    for ( ; i < 2; i++)
        atts->a[index]->precedenti[i] = -1;

    return atts;
}

ACT activityRead(FILE *file) {
    int i;
    ACT atts;

    atts = (ACT) malloc(sizeof(*atts));
    fscanf(file, "%d %d", &(atts->NA), &(atts->NP));
    for (i = 0; i < atts->NA; i++)
        atts->a[i] = ACTIVITYfile(file);
    
    for (i = 0; i < atts->NP; i++)
        atts = ACTIVITYfileVincoli(file, atts);

    return atts;
}

static int checkUntilIndex(ACT a, int index, char **selected, int curr) {
    int i, j, k;
    int *isIn;

    isIn = (int*) calloc(MAX_VINC, sizeof(int));
    for (i = 0; i < curr; i++) {
        k = ACTIVITYindex(a, selected[i]);
        if (a->a[k]->t_f >= a->a[index]->t_i && 
            a->a[k]->t_i <= a->a[index]->t_f)
            return 0;

        for (j = 0; j < MAX_VINC && a->a[index]->precedenti[j] != -1; j++) {
            if (a->a[index]->precedenti[j] == k)
                isIn[j] = 1;
        }
    }

    for (i = 0; i < MAX_VINC; i++)
        if (isIn[i] == 0)
            return 0;

    return 1;
} 

int checkSelection(ACT a, char **selected, int nsel) {
    int i, j;

    for (i = 0; i < nsel; i++) {
        j = ACTIVITYindex(a, selected[i]);
        if (j == -1)
            return 0;

        if (checkUntilIndex(a, j, selected, i) == 0)
            return 0;
    }

    return 1;
}

void disp_rip(int pos, ACT atts, char **sol, char **best_sol, int n, int *best_n, int val, int *best_val) {
    int i;

    if (pos >= atts->NA) {
        if (checkSelection(atts, sol, n) && val > *best_val) {
            *best_n = n;
            *best_val = val;
            for (i = 0; i < n; i++) {
                strcpy(best_sol[i], sol[i]);
            }
        }
        return;
    }

    sol[n] = atts->a[pos]->nome;
    disp_rip(pos+1, atts, sol, best_sol, n+1, best_n, val + atts->a[pos]->val, best_val);
    disp_rip(pos+1, atts, sol, best_sol, n, best_n, val, best_val);

    return;
}

void sortSol(ACT a, char **best_sol, int n) {
    QuickSortR(best_sol, 0, n);
}

char **bestSelection(ACT atts, int *n) {
    char **sol, **best_sol;
    sol = (char**) malloc(atts->NA * sizeof(char*));
    best_sol = (char**) malloc(atts->NA * sizeof(char*));

    disp_rip(0, atts, sol, best_sol, 0, 0, 0, 0);

    sortSol(atts, best_sol, n);

    return best_sol;
}