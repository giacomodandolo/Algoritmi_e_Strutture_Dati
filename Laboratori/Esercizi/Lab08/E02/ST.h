#ifndef ST_H
#include "Item.h"
#include "General.h"

typedef struct st_t *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item *item);
int STsearch(ST st, Key k);
void STdisplayByIndex(ST st, int i);
Item *STsearchByIndex(ST st, int i);

#endif