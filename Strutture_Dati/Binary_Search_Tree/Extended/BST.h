#ifndef BST_H
#define BST_H

typedef struct binarysearchtree *BST;

/* INIZIALIZZAZIONE */
BST BSTinit();
void BSTfree(BST bst);

/* OPERAZIONI DI DIMENSIONE */
int BSTcount(BST bst);
int BSTempty(BST bst);

/* 
    --- INSERIMENTO IN FOGLIA ---

    Se il BST è vuoto, si crea un nuovo albero, altrimenti si 
    ha inserimento ricorsivo nel sottoalbero sinistro o destro 
    a seconda del confronto tra la chiave dell'item e quella 
    del nodo corrente.

    E' presente anche la versione iterativa.
*/
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);

/* 
    --- INSERIMENTO IN RADICE ---
    
    L'inserimento ricorsivo alla radice avviene attraverso
    l'inserimento nel sottoalbero appropriato e una rotazione
    per farlo diventare radice dell'albero. 
*/
void BSTinsert_root(BST bst, Item x);

/* 
    --- CANCELLAZIONE ---

    Cancellando da un BST è necessario mantenere le
    proprietà dei BST e la struttura ad albero binario.
    Si procede così:
    1)  controllare se il nodo con l'item da cancellare
        è in uno dei sottoalberi, e in quel caso si ha la
        cancellazione ricorsiva nel sottoalbero;
    2)  se è la radice, si elimina e si ricombina in due
        sottoalberi e la nuova radice è il successore o il
        predecessore dell'item cancellato 
*/
void BSTdelete(BST bst, Key k);

/* 
    --- RICERCA --- 

    La ricerca nel BST è applicata come ricerca ricorsiva
    di un nodo che contiene un item con una chiave data
    attraverso il seguente procedimento:
    1)  percorrimento dell'albero dalla radice;
    2)  termina quando la chiave dell'item cercato è uguale
        alla chiave del nodo corrente oppure si è giunti
        ad un albero vuoto;
    3)  la ricorsione avviene dal nodo corrente sul sottoalbero
        sinistro se la chiave dell'item cercato è minore della
        chiave del nodo corrente, altrimenti su quello destro.
*/
Item BSTsearch(BST bst, Key k);

/* 
    --- SELEZIONE ---

    La selezione dell'item avviene sulla r-esima chiave più piccola
    e, definendo t come il numero di nodi del sottoalbero sinistro,
    si ha:
        t = r:  si ritorna ROOT;
        t > r:  ricorsione nel sottoalbero sinistro, alla ricerca
                della k-esima chiave più piccola;
        t < r:  ricorsione nel sottoalbero destro, alla ricerca
                della (r-t-1)-esima chiave più piccola.
*/
Item BSTselect(BST bst, int r);

/* 
    --- MIN ---

    Per ricercare il minimo nel BST si segue il puntatore al
    sottoalbero sinistro finché arriva al nodo sentinella z.
*/
Item BSTmin(BST bst);

/* 
    --- MAX ---

    Per ricercare il massimo nel BST il segue il puntatore al
    sottoalbero destro finché arriva al nodo sentinella z.
*/ 
Item BSTmax(BST bst);

/* 
    --- VISITA ---

    La visita può essere di tre tipi: 
        pre-order:
            ROOT -> LEFT -> RIGHT
        in-order: 
            LEFT -> ROOT -> RIGHT
        post-order:
            LEFT -> RIGHT -> ROOT
    
    La chiave mediana di un insieme di N elementi è
    l'elemento che si trova in posizione (n+1)/2 nella
    sequenza ordinata degli elementi dell'insieme.
*/
void BSTvisit(BST bst, int strategy);

/* 
    --- SUCCESSORE --- 

    Il successore di un item è un nodo h con un item con
    la più piccola chiave maggiore della chiave di item,
    altrimenti è l'item vuoto.

    Se esiste RIGHT, allora succ = min(RIGHT), altrimenti
    è il primo antenato il cui figlio sinistro è anche un
    antenato di h.
*/
Item BSTsucc(BST bst, Key k);

/* 
    --- PREDECESSORE ---

    Il predecessore di un item è un nodo h con un item con
    la più grande chiave minore della chiave di item, altrimenti
    è l'item vuoto.

    Se esiste LEFT, allora pred = max(LEFT), altrimenti
    è il primo antenato di h il cui figlio destro è anche
    un antenato di h.
*/
Item BSTpred(BST bst, Key k);

/* 
    --- ROTAZIONE A SINISTRA ---

    RIGHT di ROOT = LEFT di RIGHT
    LEFT di RIGHT = ROOT
*/
link rotL(link h);

/* 
    --- ROTAZIONE A DESTRA ---

    LEFT di ROOT = RIGHT di LEFT
    RIGHT di LEFT = ROOT
*/
link rotR(link h);

/* 
    --- PARTIZIONAMENTO ---

    La partizione riorganizza l'albero avendo l'item con la
    k-esima chiave più piccola nella radice attraverso il
    seguente procedimento, definendo il nodo come radice di
    un sottoalbero.
        t > k:  ricorsione nel sottoalbero sinistro, con
                partizionamento rispetto alla k-esima
                chiave più piccola, terminando con una rotazione
                a destra;
        t < k:  ricorsione nel sottoalbero destro, con
                partizionamento rispetto alla (k-t-1)-esima
                chiave più piccola, terminando con una rotazione
                a sinistra.
    
    Spesso il partizionamento si fa intorno alla chiave mediana.
*/
link partR(link h, int r);

/* 
    --- CONNESSIONE ALBERI --- 

    Si effettua la partizione dell'albero b con rango 0, e
    successivamente il suo LEFT diventa a.
*/
link joinLR(link a, link b, link z);

/* 
    --- BILANCIAMENTO --- 

    Il ribilanciamento a richiesta avviene attraverso:
    1)  un partizionamento ricorsivo attorno alla chiave mediana
        inferiore;
    2)  algoritmo di Day, Stout e Warren che costruisce un albero
        quasi completo.
*/
void BSTbalance(BST bst);

#endif