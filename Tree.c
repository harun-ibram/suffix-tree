#include "Tree.h"
#include "Queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int isEmpty(Tree tree) {
    if (tree)
        return 0;
    for (int i = 0; i < 27; i++)
        if (tree->children[i])
            return 0;
    return 1;
}

Tree createTree() {
    Tree t = calloc(1, sizeof(Node));
    t->c = '$';
    return t;
}

int whichChild(char c) {
    if (c == '$')
        return 0;
    else
        return c - 'a' + 1;
}

char whichChar(int i) {
    if (!i)
        return '$';
    else
        return i - 1 + 'a';
}

Tree insert(Tree tree, char* elem) {
    //  Daca arborele nu exista alocam memorie
    if (isEmpty(tree)) {
        Tree t = createTree();
        tree = t;
    }

    Tree iter = tree;
    int n = strlen(elem), i = n - 1;
    //  Alocam subarborele corespunzator urmatorului caracter
    iter->children[0] = createTree();
    //  i este pentru a determina sufixul din cuvant
    while (i >= 0) {
        //  Iteram prin sirul de caractere primit in timp ce introducem
        //  caracterele in arbore
        char *s = elem + i;
        iter = tree;
        int j = 0;  //  j este pentru a itera prin sufix
        while (j < n - i) {
            //  Daca exista deja caracterul doar trecem in nodul corespunzator,
            //  altfel alocam nodul inainte
            if (iter->children[whichChild(s[j])]) {
                iter = iter->children[whichChild(s[j])];
            } else {
                iter->children[whichChild(s[j])] = createTree();
                iter = iter->children[whichChild(s[j])];
            }
            //  Inscriptionam caracterul in nod
            iter->c = s[j];
            j++;
        }
        i--;
    }
    return tree;
}

void weirdBFS(FILE *out, Tree t) {
    Q prev_level;
    Q current_level = initQ();
    //  Punem primul nivel de noduri in coada
    for (int i = 0; i < 27; i++) {
        if (t->children[i])
            current_level = enq(current_level, t->children[i]);
    }

    //  Cat timp mai avem elemente de afiast
    while (!isQEmpty(current_level)) {
        //  Afisarea nivelului de noduri precedent
        prev_level = copyQueue(current_level);
        printQueue(out, prev_level);
        current_level = destroyQ(current_level);
        current_level = initQ();
        //  Adaugam urmatorul nivel de noduri in coada
        while (!isQEmpty(prev_level)) {
            Tree x = front(prev_level);
            prev_level = deq(prev_level);
            for (int i = 0; i < 27; i++) {
                if (x->children[i])
                    current_level = enq(current_level, x->children[i]);
            }
        }
        //  Eliberam nivelul deja afiast
        prev_level = destroyQ(prev_level);
        prev_level = initQ();
        fprintf(out, "\n");
    }
    //  Eliberam ambele nivele
    prev_level = destroyQ(prev_level);
    current_level = destroyQ(current_level);
}

Tree destroyTree(Tree t) {
    //  Daca nu are copii sau e vid, dezalocam
    if (isEmpty(t)) {
        if (t)
            free(t);
        return NULL;
    }
    //  Eliberam copiii din vector
    for (int i = 0; i < 27; i++) {
        if (t->children[i])
            t->children[i] = destroyTree(t->children[i]);
    }
    free(t);
    return NULL;
}

int countLeaves(Tree t) {
    //  Daca nu are copii, numaram ca frunza
    if (isEmpty(t))
        return 1;

    //  Numaram frunzele din arborele din fiecare copil
    int c = t->children[0] ? 1 : 0;
    for (int i = 0; i < 27; i++)
        if (t->children[i])
            c += countLeaves(t->children[i]);
    return c;
}

int KLengthSuffix(Tree t, int k, int current_len) {
    //  Am ajuns la lungimea cautata si exista
    // terminatorul de sufix printre copii
    if (current_len == k && t->c != '$' && t->children[0]) {
        return 1;
    }
    //  Cautam sufixele de lungimea K prin copiii nodului curent
    int c = 0;
    for (int i = 1; i < 27; i++) {
        if (t->children[i])
            c += KLengthSuffix(t->children[i], k, current_len + 1);
    }
    return c;
}

int mostDescendants(Tree t) {
    if (isEmpty(t))
        return 0;
    int c = 0, v[27] = {0};
    //  Numaram descendentii nodului curent si ai fiecarui copil
    for (int i = 0; i < 27; i++) {
        if (t->children[i]) {
            c++;
            v[i] = mostDescendants(t->children[i]);
        }
    }
    //  Comparam descendentii nodului cu cei ai copiilor
    for (int i = 0; i < 27; i++) {
        if (v[i] > c)
            c = v[i];
    }
    return c;
}

int containsSuffix(Tree t, char *s) {
    //  Formam sufixul cu terminator
    char *aux = malloc(strlen(s));
    strcpy(aux, s);
    strcat(aux, "$");
    int len = strlen(aux), i = 0;
    Tree iter = t;
    int child = whichChild(aux[0]);
    //  Iteram prin caracterele care coincid din arbore si sufix
    while (i < len) {
        if (iter->children[child]) {
            iter = iter->children[child];
            i++;
            child = whichChild(aux[i]);
        } else {
            //  Sufixul nu mai coincide
            free(aux);
            return 0;
        }
    }
    free(aux);
    return 1;
}

int countChildren(Tree t) {
    int c = 0;
    for (int i = 0; i < 27; i++) {
        if (t->children[i])
            c++;
    }
    return c;
}

CompTree compressTree(Tree t) {
    CompTree new_tree = malloc(sizeof(CompNode));
    //  Nu comprimam si terminatorul de sufix
    if (t->c == '$') {
        new_tree->prefix = malloc(2);
        strcpy(new_tree->prefix, "$");
        return new_tree;
    }
    char pref[MAX_SUFFIX_LEN] = {0};
    int j = 0;
    pref[j] = t->c;
    Tree iter = t;
    //  Comprimam prefixul pana la intalnirea unei bifurcatii
    while (countChildren(iter) == 1) {
        if (iter->children[0] || iter->c == '$')
            break;
        for (int i = 1; i < 27; i++) {
            if (iter->children[i]) {
                iter = iter->children[i];
                pref[++j] = iter->c;
                if (countChildren(iter) != 1)
                    break;
            }
        }
    }
    //  Scriem in arborele comprimat prefixul
    new_tree->prefix = malloc(strlen(pref));
    strcpy(new_tree->prefix, pref);

    //  Continuam comprimarea
    for (int i = 0; i < 27; i++)
        if (iter->children[i])
            new_tree->children[i] = compressTree(iter->children[i]);
    return new_tree;
}

void compTreeWeirdBFS(FILE* out, CompTree t) {
    Q prev_level;
    Q current_level = initQ();
    //  Punem primul nivel de noduri in coada
    for (int i = 0; i < 27; i++) {
        if (t->children[i])
            current_level = enqComp(current_level, t->children[i]);
    }

    //  Cat timp mai avem elemente de afisat
    while (!isQEmpty(current_level)) {
        //  Afisarea nivelului precedent de noduri
        prev_level = copyCompQueue(current_level);
        printCompQueue(out, prev_level);
        current_level = destroyQ(current_level);
        current_level = initQ();
        //  Adaugam urmatorul nivel de noduri in coada
        while (!isQEmpty(prev_level)) {
            CompTree x = compFront(prev_level);
            prev_level = deq(prev_level);
            for (int i = 0; i < 27; i++) {
                if (x->children[i])
                    current_level = enqComp(current_level, x->children[i]);
            }
        }
        //  Eliberam nivelul deja afisat
        prev_level = destroyQ(prev_level);
        prev_level = initQ();
        fprintf(out, "\n");
    }
    //  Eliberam ambele nivele
    prev_level = destroyQ(prev_level);
    current_level = destroyQ(current_level);
}

int isCompEmpty(CompTree tree) {
    if (tree)
        return 0;
    for (int i = 0; i < 27; i++)
        if (tree->children[i])
            return 0;
    return 1;
}

CompTree destroyCompTree(CompTree t) {
    //  Daca nu are copii sau e vid, deazalocam
    if (isCompEmpty(t)) {
        if (t)
            free(t);
        return NULL;
    }
    //  Eliberam copiii din vector
    for (int i = 0; i < 27; i++) {
        if (t->children[i])
            t->children[i] = destroyCompTree(t->children[i]);
    }
    free(t);
    return NULL;
}
