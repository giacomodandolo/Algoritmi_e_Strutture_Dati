#ifndef SET_H
#define SET_H

typedef struct set *SET;

/* INIZIALIZZAZIONE */
SET SETinit(int maxN);

/* FREE */
void SETfree(SET s);

/* INSERIMENTO */
void SETfill(SET s, Item val);

/* RICERCA */
int SETsearch(SET s, Key k);

/* OPERAZIONI INSIEMISTICHE */
SET SETunion(SET s1, SET s2);
SET SETintersection(SET s1, SET s2);

/* OPERAZIONI DI DIMENSIONE */
int SETsize(SET s);
int SETempty(SET s);

/* VISUALIZZAZIONE */
void SETdisplay(SET s);

#endif