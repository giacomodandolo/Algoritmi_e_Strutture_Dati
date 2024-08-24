#include "Item.h"

typedef struct item_t {
    char elab[MAX_LEN], net[MAX_LEN];
} Item;

typedef char* Key;

Item *ITEMsetvoid() {
    Item *new;

    new = (Item*) malloc(sizeof(Item));
    strcpy(new->elab, "");
    strcpy(new->net, "");

    return new;
}

Item *ITEMload(Item *item, char *elab, char *net) {
    strcpy(item->elab, elab);
    strcpy(item->net, net);
    
    return item;
}

void ITEMstore(Item *item) {
    printf("ID_ELAB = %s \nID_RETE = %s\n", 
            item->elab, item->net);
}

void KEYscan(Item *item) {
    printf("%s", item->elab);
}

Key KEYget(Item *item) {
    return item->elab;
}

int KEYcmp(Key k1, Key k2) {
    return strcmp(k1, k2);
}
