/* IBRAM Harun - 314CD */
#ifndef QUEUE_H
#define QUEUE_H
#include "Tree.h"

typedef struct qnode {
    Tree elem;
    struct qnode *next;
    struct qnode *prev;
    CompTree compElem;
} QNode, *QNptr;

typedef struct queue {
    QNode *first, *last;
} *Q;

/*
* Initializeaza coada goala
*/
Q initQ(void);

/*
* Aloca memorie pentru un element al cozii cu date de tip arbore atomic
*/
QNptr createQNode(Tree);

/*
* Returneaza primul element din coada
*/
Tree front(Q);

/*
* Adauga un element in coada
*/
Q enq(Q, Tree);

/*
* Elimina primul element din coada
*/
Q deq(Q);

/*
* Dezaloca memoria elementelor din coada
*/
Q destroyQ(Q);

/*
* Afiseaza elementele din coada cu date de tip arbore atomic
*/
void printQueue(FILE *, Q);

/*
* Copiaza elementele din coada primita ca parametru intr-una noua
*/
Q copyQueue(Q);

/*
* Verifica daca mai sunt elemente in coada
*/
int isQEmpty(Q);

/*
* Aloca un element pentru un nod al cozii cu date de tip arbore comprimat
*/
QNptr createCompQNode(CompTree);

/*
* Returneaza primul element din coada cu date de tip arbore comprimat
*/
CompTree compFront(Q);

/*
* Adauga un element in coada cu date de tip arbore comprimat
*/
Q enqComp(Q, CompTree);

/*
* Copiaza elementele din coada primita ca parametru intr-una noua
*/
Q copyCompQueue(Q);

/*
* Afiseaza elementele din coada cu date de tip arbore comprimat
*/
void printCompQueue(FILE *, Q);

#endif