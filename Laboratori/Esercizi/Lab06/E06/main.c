#include <stdio.h>
#include <stdlib.h>
#define STONES 4
#define MAX_FILE 50

typedef enum {
    z, r, t, s
} type;

int max(int a, int b) {
    return a>b ? a:b;
}

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

int ****malloc4d(int dim_z, int dim_r, int dim_t, int dim_s) {
    int ****new, i, j, k, l;

    new = (int****) malloc((dim_z+1)*sizeof(int***));
    for (i = 0; i <= dim_z; i++) {
        new[i] = (int***) malloc((dim_r+1)*sizeof(int**));
        for (j = 0; j <= dim_r; j++) {
            new[i][j] = (int**) malloc((dim_t+1)*sizeof(int*));
            for (k = 0; k <= dim_t; k++) {
                new[i][j][k] = (int*) malloc((dim_s+1)*sizeof(int));
                for (l = 0; l <= dim_s; l++)
                    new[i][j][k][l] = -1;
            }
        }
    }

    return new;
}

void free4d(int ****mat, int dim_z, int dim_r, int dim_t) {
    int i, j, k;
    
    for (i = 0; i < dim_z; i++) {
        for (j = 0; j < dim_r; j++) {
            for (k = 0; k < dim_t; k++)
                free(mat[i][j][k]);
            free(mat[i][j]);
        }
        free(mat[i]);
    }   
    free(mat);
}

int fz(int ****mz, int ****mr, int ****mt, int ****ms, int *val);
int fr(int ****mz, int ****mr, int ****mt, int ****ms, int *val);
int ft(int ****mz, int ****mr, int ****mt, int ****ms, int *val);
int fs(int ****mz, int ****mr, int ****mt, int ****ms, int *val);


int fz(int ****mz, int ****mr, int ****mt, int ****ms, int *val) {
    int res_z, res_r, res;

    if (val[z] == 0)
        return 0;
    
    if (mz[val[z]][val[r]][val[t]][val[s]] != -1)
        return mz[val[z]][val[r]][val[t]][val[s]];

    val[z]--;
    res_z = fz(mz, mr, mt, ms, val);
    res_r = fr(mz, mr, mt, ms, val);
    val[z]++;

    res = max(res_z, res_r) + 1;
    mz[val[z]][val[r]][val[t]][val[s]] = res;

    return res;
}

int fr(int ****mz, int ****mr, int ****mt, int ****ms, int *val) {
    int res_s, res_t, res;

    if (val[r] == 0)
        return 0;
    
    if (mr[val[z]][val[r]][val[t]][val[s]] != -1)
        return mz[val[z]][val[r]][val[t]][val[s]];

    val[r]--;
    res_s = fs(mz, mr, mt, ms, val);
    res_t = ft(mz, mr, mt, ms, val);
    val[r]++;

    res = max(res_s, res_t) + 1;
    mr[val[z]][val[r]][val[t]][val[s]] = res;

    return res;
}

int ft(int ****mz, int ****mr, int ****mt, int ****ms, int *val) {
    int res_z, res_r, res;

    if (val[t] == 0)
        return 0;
    
    if (mt[val[z]][val[r]][val[t]][val[s]] != -1)
        return mz[val[z]][val[r]][val[t]][val[s]];

    val[t]--;
    res_z = fz(mz, mr, mt, ms, val);
    res_r = fr(mz, mr, mt, ms, val);
    val[t]++;

    res = max(res_z, res_r) + 1;
    mt[val[z]][val[r]][val[t]][val[s]] = res;

    return res;
}

int fs(int ****mz, int ****mr, int ****mt, int ****ms, int *val) {
    int res_s, res_t, res;

    if (val[s] == 0)
        return 0;
    
    if (ms[val[z]][val[r]][val[t]][val[s]] != -1)
        return mz[val[z]][val[r]][val[t]][val[s]];

    val[s]--;
    res_s = fs(mz, mr, mt, ms, val);
    res_t = ft(mz, mr, mt, ms, val);
    val[s]++;

    res = max(res_s, res_t) + 1;
    ms[val[z]][val[r]][val[t]][val[s]] = res;

    return res;
}

int find_length(int *val) {
    int ****mz, ****mr, ****mt, ****ms, res, tmp, dim_z, dim_r, dim_t, dim_s;

    dim_z = val[z];
    dim_r = val[r];
    dim_t = val[t];
    dim_s = val[s];

    mz = malloc4d(dim_z, dim_r, dim_t, dim_s);
    mr = malloc4d(dim_z, dim_r, dim_t, dim_s);
    mt = malloc4d(dim_z, dim_r, dim_t, dim_s);
    ms = malloc4d(dim_z, dim_r, dim_t, dim_s);
    
    res = fz(mz, mr, mt, ms, val);
    tmp = fr(mz, mr, mt, ms, val);
    res = max(res, tmp);
    tmp = ft(mz, mr, mt, ms, val);
    res = max(res, tmp);
    tmp = fs(mz, mr, mt, ms, val);
    res = max(res, tmp);

    free4d(mz, dim_z, dim_r, dim_t);
    free4d(mr, dim_z, dim_r, dim_t);
    free4d(mt, dim_z, dim_r, dim_t);
    free4d(ms, dim_z, dim_r, dim_t);

    return res;
}

int main(void) {
    int i, max_len, **tests, num_tests;
    char filename[MAX_FILE];
    FILE *file;

    printf("Nome file: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    tests = readStones(file, &num_tests);
    fclose(file);

    for (i = 0; i < num_tests; i++) {
        max_len = find_length(tests[i]);
        printf("Test #%d\n", i+1);
        printf("z = %d | r = %d | t = %d | s = %d\n", tests[i][z], tests[i][r], tests[i][t], tests[i][s]);
        printf("Lunghezza = %d\n\n", max_len);
    }

    return 0;
}