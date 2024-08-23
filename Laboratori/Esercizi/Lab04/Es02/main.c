#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 50+1
#define MAX_CODE 5+1
#define MAX_FILE 50+1

typedef struct date {
    int day, month, year;
} Date;

typedef struct item {
    char code[MAX_CODE], name[MAX_STR], surname[MAX_STR], street[MAX_STR], city[MAX_STR];
    Date *birthdate;
    int cap;
} Item;

typedef struct node *link;

typedef struct node {
    Item *item;
    link next;
} Node;

Date *newDate(int day, int month, int year) {
    Date *new;
    
    new = (Date*) malloc(sizeof(Date));
    new->day = day;
    new->month = month;
    new->year = year;

    return new;
}

Item *newItem(char *code, char *name, char *surname, Date *birthdate, char *street, char *city, int cap) {
    Item *new;
    
    new = (Item*) malloc(sizeof(Item));
    strcpy(new->code, code);
    strcpy(new->name, name);
    strcpy(new->surname, surname);
    new->birthdate = birthdate;
    strcpy(new->street, street);
    strcpy(new->city, city);
    new->cap = cap;

    return new;
}

void printItem(Item *item) {
    if (item == NULL)
        return;

    printf("Codice: %s \nNome: %s \nCognome: %s \nData di nascita:%d/%d/%d \nVia: %s \nCitta': %s \nCAP: %d \n\n",
            item->code, item->name, item->surname, 
            item->birthdate->day, item->birthdate->month, item->birthdate->year, 
            item->street, item->city, item->cap);
}

void printItemFile(FILE* file, Item *item) {
    fprintf(file, "%s %s %s %d/%d/%d %s %s %d\n",
            item->code, item->name, item->surname,
            item->birthdate->day, item->birthdate->month, item->birthdate->year,
            item->street, item->city, item->cap);
}

link newNode(Item *item, link next) {
    link new;

    new = (link) malloc(sizeof(Node));
    if (new == NULL)
        return NULL;
    new->item = item;
    new->next = next;

    return new;
}

int KEYless(Date *d1, Date *d2) {
    if (d1->year < d2->year)
        return 1;
    if (d1->year == d2->year && d1->month < d2->month)
        return 1;
    if (d1->year == d2->year && d1->month == d2->month && d1->day < d2->day)
        return 1;

    return 0;
}

int KEYgreater(Date *d1, Date *d2) {
    if (d1->year > d2->year)
        return 1;
    if (d1->year == d2->year && d1->month > d2->month)
        return 1;
    if (d1->year == d2->year && d1->month == d2->month && d1->day > d2->day)
        return 1;

    return 0;
}

Item *listSearchCode(link h, char *code) {
    link x;

    for (x = h; x != NULL; x = x->next)
        if (strcmp(x->item->code, code) == 0)
            return x->item;
    
    return NULL;
}

link listInsSort(link h, Item *item) {
    link x, p;
    Date key = *(item->birthdate);

    if (listSearchCode(h, item->code) != NULL)
        return h;

    if (h == NULL || !KEYless(&key, h->item->birthdate))
        return newNode(item, h);
    
    for (p = h, x = h->next; x != NULL && KEYless(&key, x->item->birthdate); p = x, x = x->next);
    p->next = newNode(item, x);

    return h;
}

link listInsInput(link h) {
    char code[MAX_CODE], name[MAX_STR], surname[MAX_STR], street[MAX_STR], city[MAX_STR];
    int day, month, year, cap;
    Date *date;
    Item *item;

    printf("Inserisci i dati necessari: \n");
    printf("Codice: "); scanf("%s", code);
    printf("Nome: "); scanf("%s", name);
    printf("Cognome: "); scanf("%s", surname);
    printf("Data di nascita (dd/mm/yyyy): "); scanf("%d/%d/%d", &day, &month, &year);
    printf("Via: "); scanf("%s", street);
    printf("Citta': "); scanf("%s", city);
    printf("CAP: "); scanf("%d", &cap);
    
    date = newDate(day, month, year);
    item = newItem(code, name, surname, date, street, city, cap);
    h = listInsSort(h, item);
    
    return h;
}

link listInsFile(link h, FILE *file) {
    char code[MAX_CODE], name[MAX_STR], surname[MAX_STR], street[MAX_STR], city[MAX_STR];
    int day, month, year, cap;
    Date *date;
    Item *item;

    while (fscanf(file, "%s %s %s %d/%d/%d %s %s %d", code, name, surname, &day, &month, &year, street, city, &cap) == 9) {
        date = newDate(day, month, year);
        item = newItem(code, name, surname, date, street, city, cap);
        h = listInsSort(h, item);
    }
    
    return h;
}

Item *listExtractCode(link h, char *code) {
    link x, p;
    Item *item;

    if (h == NULL)
        return NULL;

    if (strcmp(h->item->code, code) == 0) {
        item = h->item;
        free(h);
        return item;
    }

    for (p = h, x = h->next; x != NULL; p = x, x = x->next)
        if (strcmp(x->item->code, code) == 0) {
            item = x->item;
            p->next = x->next;
            return item;
        }

    return NULL;
}

link listExtractDates(link h, Date *d1, Date *d2) {
    link x, p1, p2, e;

    if (h == NULL || KEYgreater(d1, d2))
        return NULL;

    if (KEYless(h->item->birthdate, d2)) {
        e = h;
        x = h;
    } else {
        for (p1 = h, x = h->next; x != NULL && KEYgreater(x->item->birthdate, d2); p1 = x, x = x->next);
        e = x;
    }
    for (p2 = x, x = e->next; x != NULL && KEYgreater(x->item->birthdate, d1); p2 = x, x = x->next);
    p1->next = x;
    p2->next = NULL;

    return e;
}

void printListFile(link h, FILE* file) {
    link x;

    for (x = h; x != NULL; x = x->next) {
        printItemFile(file, x->item);
    }
}

int main(void) {
    int choice, day, month, year;
    char filename[MAX_FILE], code[MAX_CODE];
    link head, extr, x;
    Date *d1, *d2;
    FILE *file;

    head = NULL;
    while (1) {
        printf("Scegli: \n 0. Termina il programma;\n 1. Inserimento in lista da tastiera;\n 2. Inserimento in lista da file;\n 3. Ricerca per codice;\n 4. Cancellazione per codice;\n 5. Cancellazione tra due date;\n 6. Stampa su file.\n");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                if(file != NULL)
                    fclose(file);
                return 0;
            case 1:
                head = listInsInput(head);
                printItem(head->item);
                break;
            case 2:
                printf("Inserisci il nome del file: ");
                scanf("%s", filename);
                file = fopen(filename, "r");
                head = listInsFile(head, file);
                fclose(file);
                break;
            case 3:
                printf("Inserisci il codice: ");
                scanf("%s", code);
                printItem(listSearchCode(head, code));
                break;
            case 4:
                printf("Inserisci il codice: ");
                scanf("%s", code);
                printItem(listExtractCode(head, code));
                break;
            case 5:
                printf("Inserisci la prima data (dd/mm/yyyy): "); scanf("%d/%d/%d", &day, &month, &year);
                d1 = newDate(day, month, year);
                printf("Inserisci la prima data (dd/mm/yyyy): "); scanf("%d/%d/%d", &day, &month, &year);
                d2 = newDate(day, month, year);
                extr = listExtractDates(head, d1, d2);
                for (x = extr; x != NULL; x = x->next)
                    printItem(x->item);
                break;
            case 6:
                printf("Inserisci il nome del file: ");
                scanf("%s", filename);
                file = fopen(filename, "w");
                printListFile(head, file);
                fclose(file);
                break;
            default:
                printf("Inserisci una scelta valida.\n");
        }
    }
}