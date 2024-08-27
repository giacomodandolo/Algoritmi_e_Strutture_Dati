#ifndef STACK_H
#define STACK_H

/* INIZIALIZZAZIONE */
void STACKinit(int maxN);

/* OPERAZIONI DI DIMENSIONE */
int STACKempty();

/* INSERIMENTO */
void STACKpush(Item val);

/* ESTRAZIONE */
Item STACKpop();

#endif