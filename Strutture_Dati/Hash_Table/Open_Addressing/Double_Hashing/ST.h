#ifndef ST_H
#define ST_H

typedef struct symboltable *ST;

void STinsert(ST st, Item item);
Item STsearch(ST st, Key k);
void STdelete(ST st, Key k);

#endif