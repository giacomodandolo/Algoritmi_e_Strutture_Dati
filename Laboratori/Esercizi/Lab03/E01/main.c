#include <stdio.h>


int majorityR(int *a, int l, int r, int *count) {
    int i, N, m, countL = 0, majL, countR = 0, majR;
    
    if (l == r) {
        *count = 1;
        return a[l];
    }

    m = (l+r)/2;
    majL = majorityR(a, l, m, &countL);
    majR = majorityR(a, m+1, r, &countR);

    if (majL == majR) {
        *count = countL + countR;
        return majL;
    }

    N = r - l;
    
    if (majL == -1) {
        for (i = l; i < m; i++)
            if (a[i] == majR)
                countR++;
        if (countR > N/2) {
            *count = countR;
            return majR;
        }
    }

    if (majR == -1) {
        for (i = m+1; i < r; i++)
            if (a[i] == majL)
                countL++;
        if (countL > N/2) {
            *count = countL;
            return majL;
        }
    }

    return -1;
}

int majority(int *a, int N) {
    int count = 0;
    return majorityR(a, 0, N, &count);
}

int main(void) {
    int N = 7, a[7] = {3, 3, 3, 3, 4, 5, 5};
    printf("%d", majority(a, N));

    return 0;
}