/* IBRAM Harun - 314CD */
#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#define MAX_SUFFIX_LEN 256
#define MAX_CHILDREN 27

typedef struct tnode {
    struct tnode *children[MAX_CHILDREN];
    char c;
} Node, *Tree;

typedef struct compressed_tree_node {
    struct compressed_tree_node *children[MAX_CHILDREN];
    char *prefix;
} CompNode, *CompTree;

/*
* Verifica daca arborele exista si daca are copii
*/
int isEmpty(Tree);

/*
* Aloca memorie pentru un arbore atomic vid
*/
Tree createTree();

/*
* Determina ce indice din vectorul de copii ii corespunde caracterului primit
*/
int whichChild(char);

/*
* Determina ce caracter ii corespunde indicelui primit (valori 0-26)
*/
char whichChar(int);

/*
* Insereaza un sufix primit ca parametru in arborele atomic.
* Sufixul trebuie sa aiba caracterul '$' la final.
*/
Tree insert(Tree, char*);

/*
* Parcurgere in latime care afiseaza pe nivele arborele atomic in fisierul primit ca parametru
*/
void weirdBFS(FILE*, Tree);

/*
* Dezaloca memoria pentru arborele atomic
*/
Tree destroyTree(Tree);

/*
* Returneaza numarul de frunze din arborele atomic
*/
int countLeaves(Tree);

/*
* Returneaza numarul de sufixe de lungime K, primit ca parametru.
* Al treilea parametru reprezinta lungimea curenta a sufixului
* si trebuie sa fie 0 la apelarea functiei
*/
int KLengthSuffix(Tree, int, int);

/*
* Determina numarul maxim de descendenti ai unui singur nod din arbore
*/
int mostDescendants(Tree);

/*
* Verifica daca sufixul primit exista in arbore
*/
int containsSuffix(Tree, char*);

/*
* Determina numarul de copii ai nodului primit ca parametru
*/
int countChildren(Tree);

/*
* Comprima prefixele comune din arborele atomic
*/
CompTree compressTree(Tree);

/*
* Parcurgere in latime care afiseaza pe nivele arborele comprimat
*/
void compTreeWeirdBFS(FILE *, CompTree);

/*
* Verifica daca arborele comprimat exista si daca are copii
*/
int isCompEmpty(CompTree);

/*
* Dezaloca memoria pentru arborele comprimat
*/
CompTree destroyCompTree(CompTree);
#endif