#ifndef ITEM_H
#define ITEM_H

typedef struct item { 
    int low; 
    int high; 
} Item;

/* INIZIALIZZAZIONE */
Item ITEMscan();
Item ITEMsetVoid();

/* CONTROLLO */
int ITEMcheckVoid(Item val);
int ITEMoverlap(Item val1, Item val2);
int ITEMeq(Item val1, Item val2);
int ITEMlt(Item val1, Item val2);
int ITEMlt_int(Item val1, int val2);

/* VISUALIZZAZIONE */
void ITEMstore(Item val);

/* OTTENIMENTO */
int ITEMhigh();
int ITEMlow();

#endif