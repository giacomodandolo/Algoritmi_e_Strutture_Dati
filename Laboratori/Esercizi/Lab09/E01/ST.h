#ifndef ST_H
#include "General.h"

typedef struct st_t *ST;
typedef char Key;

ST STinit(int maxN);
void STfree(ST st);
void STinsert(ST st, char c);
char STsearchByIndex(ST st, int i);
int STsearch(ST st, Key k);

#endif