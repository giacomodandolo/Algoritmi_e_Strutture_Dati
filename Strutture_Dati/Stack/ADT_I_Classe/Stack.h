#ifndef STACK_H
#define STACK_H

typedef struct stack *STACK;

/* INIZIALIZZAZIONE */
void STACKinit(int maxN);

/* OPERAZIONI DI DIMENSIONE */
int STACKempty(STACK s);

/* INSERIMENTO */
void STACKpush(STACK s, Item val);

/* ESTRAZIONE */
Item STACKpop(STACK s);

#endif