#ifndef ITEM_H
#define MAX_LEN 30
#include "General.h"

typedef struct item_t Item;
typedef char* Key;

Item *ITEMsetvoid();
Item *ITEMload(Item *item, char *elab, char *net);
void ITEMstore(Item *item);
void KEYscan(Item *item);
Key KEYget(Item *item);
int KEYcmp(Key k1, Key k2);

#endif