#include "ST.h"

/* METODO MOLTIPLICATIVO */
int hash(float k, int M, float s, float t) {
    return ((k-s)/(t-s))*M;
}

/* METODO MODULARE */
int hash(int k, int M) {
    return (k%M);
}

/* METODO DI HORNER */
int hash(char *v, int M) { 
    int h = 0, base = 128;

    for (; *v != '\0'; v++)
        h = (base * h + *v) % M;
    
    return h;
}

/* CHIAVI STRINGA CON BASE PRIMA */
int hash(char *v, int M) { 
    int h = 0, base = 127;

    for (; *v != '\0'; v++)
        h = (base * h + *v) % M;

    return h;
}

/* CHIAVI STRINGA CON HASH UNIVERSALE */
int hashU(char *v, int M) { 
    int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;

    return h;
}
