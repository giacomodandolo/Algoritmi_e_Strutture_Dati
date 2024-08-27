#ifndef ITEM_H
#define ITEM_H
#define MAXC 30

/* --- QUASI ADT --- */

/* Tipo 1 */
typedef int Item;
typedef int Key;

/* Tipo 2 */
typedef char *Item;
typedef char *Key;

/* Tipo 3 */
typedef struct item {
    char name[MAXC];
    int num;
} Item;
typedef char *Key;

/* Tipo 4 */
typedef struct item {
    char *name;
    int num;
} Item;
typedef char *Key;

/* --- KEY --- */
int KEYcompare(Key k1, Key k2);
Key KEYscan();

/* KEY (1/2) */
Key KEYget(Item val);

/* KEY (3/4) */
Key KEYget(Item *pval);

/* --- ITEM --- */
Item ITEMscan();
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2);
int ITEMgreater(Item val1, Item val2);
int ITEMcheckvoid(Item val);
Item ITEMsetvoid();

/* --- ADT I° CLASSE --- */
typedef struct item *Item;
typedef char *Key;

/* --- KEY --- */
Key KEYget(Item val);
Key KEYscan();
int KEYcompare(Key k1, Key k2);

/* --- ITEM --- */
Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan();
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2);
int ITEMgreater(Item val1, Item val2);
int ITEMcheckvoid(Item val);
Item ITEMsetvoid();

#endif