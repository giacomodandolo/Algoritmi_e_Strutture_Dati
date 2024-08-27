#include "Item.h"

/* --- QUASI ADT --- */

/* TIPO 1 */
Key KEYget(Item val) {
    return val;
}

int KEYcompare (Key k1, Key k2) {
    return (k1-k2);
}

Item ITEMscan() {
    Item val;

    scanf("%d", &val);

    return val;
}
void ITEMshow(Item val) {
    printf("%d", val);
}

int ITEMless(Item val1, Item val2) {
    return (KEYget(val1) < KEYget(val2));
}

int ITEMgreater(Item val1, Item val2) {
    return (KEYget(val1) > KEYget(val2));
}

/* TIPO 2 */
static char buf[MAXC];

Key KEYget(Item val) {
    return val;
}

int KEYcompare (Key k1, Key k2) {
    return (strcmp(k1, k2));
}

Item ITEMscan() {
    scanf("%s", buf);
    return strdup(buf);
}

void ITEMshow(Item val) {
    printf("%s", val);
}

int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(val1), KEYget(val2)) < 0);
}

int ITEMgreater(Item val1, Item val2) {
    return (strcmp(KEYget(val1), KEYget(val2)) > 0);
}

/* TIPO 3 */
Key KEYget(Item *pval) {
    return (pval->name);
}

int KEYcompare (Key k1, Key k2) {
    return (strcmp(k1,k2));
}

Item ITEMscan() {
    Item val; 
    
    scanf("%s %d", val.name, &(val.num));
    
    return val;
}

void ITEMshow(Item val) {
    printf("%s %d", val.name, val.num);
}

int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(&val1), KEYget(&val2)) < 0);
}

int ITEMgreater(Item val1, Item val2) {
    return (strcmp(KEYget(&val1), KEYget(&val2)) > 0);
}

/* TIPO 4 */
static char buf[MAXC];

Key KEYget(Item *pval) {
    return (pval->name);
}

int KEYcompare (Key k1, Key k2) {
    return (strcmp(k1, k2));
}

Item ITEMscan() {
    Item val;

    scanf("%s %d", buf, &(val.num));
    val.name = strdup(buf);

    return val;
}

void ITEMshow(Item val) {
    printf("%s %d", val.name, val.num);
}

int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(&val1), KEYget(&val2)) < 0);
}

int ITEMgreater(Item val1, Item val2) {
    return (strcmp(KEYget(&val1), KEYget(&val2)) > 0);
}

/* --- ADT I° CLASSE --- */

/* TIPO 3 */
struct item {
    char name[MAXC];
    int num;
};

Item ITEMnew(void) {
    Item val = (Item) malloc(sizeof(struct item));
    
    if (val == NULL)
        return ITEMsetvoid();
    val->name[0] = '\0';
    val->num = 0;

    return val;
}

void ITEMfree(Item val) {
    free(val);
}

Item ITEMscan() {
    Item val = ITEMnew();
    
    if (val != NULL) {
        scanf("%s %d", val->name, &val->num);
    }
    
    return val;
}

/* TIPO 4 */
static char buf[MAXC];
struct item {
    char *name;
    int num;
};

Item ITEMnew(void) {
    Item val = (Item) malloc(sizeof(struct item));
    
    if (val == NULL)
        return ITEMsetvoid();
    val->name = NULL;
    val->num = 0;
    
    return val;
}
void ITEMfree(Item val) {
    if (val->name != NULL) 
        free(val->name);
    free(val);
}

Item ITEMscan() {
    Item val = ITEMnew();

    if (val != NULL) {
        scanf("%s %d", buf, &val->num);
        val->name = strdup(buf);
    }
    
    return val;
}

void ITEMscan(Item val) {
    scanf("%s %d", buf, &val->num);
    val->name = strdup(buf);
}

/* FUNZIONI COMUNI */
Key KEYget(Item val) {
    return (val->name);
}

int KEYcompare (Key k1, Key k2) {
    return (strcmp(k1, k2));
}

void ITEMshow(Item val) {
    printf("%s %d", val->name, val->num);
}

int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(val1), KEYget(val2)) < 0);
}

int ITEMgreater(Item val1, Item val2) {
    return (strcmp(KEYget(val1), KEYget(val2)) > 0);
}
