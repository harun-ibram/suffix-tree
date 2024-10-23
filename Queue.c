/* IBRAM Harun - 314CD */
#include "Queue.h"
#include <string.h>
#include <stdlib.h>

Q initQ() {
    Q q = malloc(sizeof(struct queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}

QNptr createQNode(Tree t) {
    QNptr x = malloc(sizeof(QNode));
    x->elem = t;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

QNptr createCompQNode(CompTree t) {
    QNptr x = malloc(sizeof(QNode));
    x->compElem = t;
    x->next = NULL;
    x->prev = NULL;
    return x;
}

Tree front(Q q) {
    if (!isQEmpty(q))
        return q->first->elem;
    return NULL;
}

CompTree compFront(Q q) {
    if (!isQEmpty(q))
        return q->first->compElem;
    return NULL;
}

Q enq(Q q, Tree t) {
    // In cazul in care coada nu exista, o cream
    if (q == NULL)
        q = initQ();
    // Cazul in care adaugam in coada vida
    if (q->first == NULL) {
        QNptr n = createQNode(t);
        q->first = n;
        q->last = n;
        return q;
    }
    // Cazul genereal de inserare la finalul cozii
    QNptr n = createQNode(t);
    q->last->next = n;
    n->prev = q->last;
    q->last = n;
    return q;
}

Q enqComp(Q q, CompTree t) {
    // In cazul in care coada nu exista, o cream
    if (q == NULL)
        q = initQ();
    // Cazul in care adaugam in coada vida
    if (q->first == NULL) {
        QNptr n = createCompQNode(t);
        q->first = n;
        q->last = n;
        return q;
    }
    // Cazul genereal de inserare la finalul cozii
    QNptr n = createCompQNode(t);
    q->last->next = n;
    n->prev = q->last;
    q->last = n;
    return q;
}

Q deq(Q q) {
    // In cazul in care coada nu exista nu facem nimic
    if (q == NULL || q->first == NULL)
        return q;

    // Modificarea legaturilor
    QNptr tmp = q->first;
    q->first = q->first->next;
    if (q->first != NULL)
        q->first->prev = NULL;

    // Eliberearea memoriei pentru elementul eliminat
    free(tmp);
    return q;
}

Q destroyQ(Q q) {
    // In cazul in care coada nu exista nu facem nimic
    if (q == NULL)
        return q;

    // Eliberare tuturor elementelor din coada
    while (q->first != NULL)
        q = deq(q);

    // Eliberarea memoriei pentru coada
    free(q);
    return NULL;
}


void printQueue(FILE *out, Q q) {
    if (!q || !q->first)
        return;
    QNptr iter = q->first;
    while (iter != NULL) {
        fprintf(out, "%c ", iter->elem->c);
        iter = iter->next;
    }
}

void printCompQueue(FILE *out, Q q) {
    if (!q || !q->first)
        return;
    QNptr iter = q->first;
    while (iter != NULL) {
        fprintf(out, "%s ", iter->compElem->prefix);
        iter = iter->next;
    }
}


Q copyQueue(Q q) {
    if (isQEmpty(q))
        return NULL;
    Q copy = initQ();
    QNptr iter = q->first;
    while (iter) {
        copy = enq(copy, iter->elem);
        iter = iter->next;
    }
    return copy;
}

Q copyCompQueue(Q q) {
    if (isQEmpty(q))
        return NULL;
    Q copy = initQ();
    QNptr iter = q->first;
    while (iter) {
        copy = enqComp(copy, iter->compElem);
        iter = iter->next;
    }
    return copy;
}

int isQEmpty(Q q) {
    if (q == NULL || q->first == NULL)
        return 1;
    return 0;
}
