#ifndef ST_H
#define ST_H

/* 
    --- QUADRATIC PROBING ---
*/

typedef struct symboltable *ST;

/* 
    --- INSERIMENTO ---

    L'inserimento avviene utilizzando i come il contatore dei
    tentativi. Si utilizza l'index (h'(k) + c1*i + c_2*i^2)%M.
    Se la posizione è libera si inserisce la chiave, altrimenti
    si incrementa i e si ripete fino a cella vuota.
*/
void STinsert(ST st, Item item);

/* RICERCA */
Item STsearch(ST st, Key k);

/* CANCELLAZIONE */
void STdelete(ST st, Key k);

#endif