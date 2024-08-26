#include "Quotazione.h"

Quot *QUOTsetvoid() {
    Quot *x;

    x = (Quot*) malloc(sizeof(Quot));
    x->data = DATAload(0, 0, 0);
    x->ora = ORAload(0, 0);
    x->val = 0;
    x->num = 0;
    x->tot = 0;

    return x;
}

Quot *QUOTload(Data *data, Ora *ora, int val, int num) {
    Quot *x;

    x = QUOTsetvoid();
    x->data = data;
    x->ora = ora;
    x->val = val;
    x->num = num;
    x->tot = val*num;

    return x;
}

void QUOTstore(FILE* file, Quot *q) {
    printf("\nData = ");
    DATAstore(file, q->data);
    printf("\nOra = ");
    ORAstore(file, q->ora);
    printf("\nVal = %d\nNum = %d\nTot = %d\n", q->val, q->num, q->tot);
}

KeyQ *QUOTgetKey(Quot *q) {
    return q->data;
}

int QUOTgetTot(Quot *q) {
    return q->tot;
}

int QUOTcmpKey(KeyQ *k1, KeyQ *k2) {
    return DATAcmp(k1, k2);
}

