#ifndef ST_H
#define ST_H

/* 
    --- LINEAR PROBING ---

    L'inserimento avviene calcolando i = h(k). Se la posizione
    è libera si inserisce la chiave, altrimenti incrementa di un
    modulo M. Si ripete fino alla cella vuota.
*/

typedef struct symboltable *ST;

/* INIZIALIZZAZIONE */
ST  STinit(int maxN, float r);

/* OPERAZIONI DI DIMENSIONE */
int full(ST st, Item item);

/* 
    --- INSERIMENTO ---
    
    L'inserimento avviene calcolando i = h(k). Se la posizione
    è libera si inserisce la chiave, altrimenti incrementa di un
    modulo M. Si ripete fino alla cella vuota.
*/
void STinsert(ST st, Item val);

/* 
    --- RICERCA ---

    La ricerca avviene calcolando i = h(k). Se la chiave è trovata,
    si termina con successo, altrimenti si incrementa i di un
    modulo M. Si ripete fino a cella vuota.
*/
Item STsearch(ST st, Key k);

/* 
    --- CANCELLAZIONE ---

    La cancellazione è un'operazione complessa che interrompe le
    catene di collisione. Ci sono due soluzioni:
    1)  sostituire la chiave cancellata con una chiave sentinella
        che conta come piena in ricerca e vuota in inserzione;
    2)  reinserire le chiavi del cluster sottostante la chiave
        cancellata.
*/
void STdelete(ST st, Key k);

#endif