#include <stdio.h>

void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int gcd(int a, int b) {
    int a_odd, b_odd, res;
    
    if (a == 0 || a == 1)
        return b;        
    if (b == 0)
        return a;

    if (a < b)
        swap(&a, &b);

    a_odd = a%2;
    b_odd = b%2;
    if (a_odd && b_odd)
        res = gcd((a-b)/2, b);
    else if (a_odd && !b_odd)
        res = gcd(a, b/2);
    else if (!a_odd && b_odd)
        res = gcd(a/2, b);
    else
        res = 2*gcd(a/2, b/2);

    return res;
}

int main(void) {
    int a, b;
    
    printf("Valori gcd: ");
    scanf("%d %d", &a, &b);

    printf("gcd: %d", gcd(a,b));

    return 0;
}