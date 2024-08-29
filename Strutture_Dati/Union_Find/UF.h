#ifndef UT_H
#define UT_H

void UFinit(int N);

/* 
    --- RICERCA ---

    Ricerca la radice del nodo p e la radice del nodo q, e vengono
    confrontate per capire se i nodi sono nello stesso albero UF. 
*/
int UFfind(int p, int q);

/* 
    --- UNIONE ---

    Ricerca la radice del nodo p e la radice del nodo q.
    Se sono uguali, sono già uniti, altrimenti si uniscono
    con una strategia pesata.
*/
void UFunion(int p, int q);

#endif