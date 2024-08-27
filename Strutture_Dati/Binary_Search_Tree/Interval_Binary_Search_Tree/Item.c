#include "Item.h"

Item ITEMscan() {
    Item val;
    printf("low = "); 
    scanf("%d", &val.low);
    printf("high = "); 
    scanf("%d", &val.high);
    return val;
}

void ITEMstore(Item val) {
    printf("[%d, %d] ", val.low, val.high);
}

Item ITEMsetVoid() {
    Item val = {-1, -1};
    return val;
}

int ITEMcheckVoid(Item val) {
    if ((val.low == -1) && (val.high == -1))
        return 1;
    return 0;
}

int ITEMoverlap(Item val1, Item val2) {
    if ((val1.low <= val2.high) && (val2.low<= val1.high))
        return 1;
    return 0;
}

int ITEMeq(Item val1, Item val2) {
    if ((val1.low == val2.low) && (val1.high == val2.high))
        return 1;
    return 0;
}

int ITEMlt(Item val1, Item val2) {
    if ((val1.low < val2.low))
        return 1;
    return 0;
}

int ITEMlt_int(Item val1, int val2) {
    if ((val1.low < val2))
        return 1;
    return 0;
}

int ITEMhigh(Item val) { 
    return val.high; 
}

int ITEMlow(Item val) { 
    return val.low; 
}
