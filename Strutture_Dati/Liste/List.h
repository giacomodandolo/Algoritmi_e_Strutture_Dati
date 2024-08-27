#ifndef LIST_H
#define LIST_H

typedef int Item;
typedef int Key;

/* TIPO 1 */
struct node { 
    Item val; 
    struct node *next;
};

/* TIPO 2 */
typedef struct node { 
    Item val; 
    struct node *next;
} node_t, *link;

/* TIPO 3 */
typedef struct node *link;
struct node {
    Item val;
    link next;
};

/* TIPO 4 */
typedef struct node node_t;
struct node {
    Item val;
    node_t *next;
};

/* TIPO 5 */
typedef struct node *link, node_t;
struct node {
    Item val;
    link next;
};

/* LISTA CONCATENATA DOPPIA */
typedef struct node *link, node_t;

struct node { 
    Item val; 
    link next;
    link prev;
};

/* --- ITEM --- */

Key KEYget(Item d);
int KEYeq(Key k1, Key k2);
int KEYless(Key k1, Key k2);
int KEYgreater(Key k1, Key k2);
void ITEMdisplay(Item d);
Item ITEMsetvoid();

/* --- LIST --- */

/* NUOVO NODO */
link newNode(Item val, link next);

/* INSERIMENTO IN TESTA */
link listInsHead(link h, Item val);
void listInsHeadP(link *hp, Item val);

/* INSERIMENTO IN CODA */
link listInsTail(link h, Item val);
void listInsTailP(link *hp, Item val);
void listInsTFast(link *hp,link *tp, Item val);
link SortListIns(link h, Item val);

/* ATTRAVERSAMENTO */
void listTravR(link h);
void listRevTravR(link h);

/* RICERCA */
Item listSearch(link h, Key k);
Item SortListSearch(link h, Key k);

/* CANCELLAZIONE */
link listDelHead(link h);
link listDelKey(link h, Key k);
link listDelKeyR(link x, Key k);
link SortListDel(link h, Key k);

/* ESTRAZIONE */
Item listExtrHeadP(link *hp);
Item listExtrKeyP(link *hp, Key k);

/* INVERSIONE LISTA */
link listReverseF(link x);

/* ORDINAMENTO LISTA */
link listSortF(link h);

#endif