#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"
#include "Queue.h"

#define ERROR "Error: Wrong arguments\n"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("%s", ERROR);
        return -1;
    }
    if (!strcmp(argv[1], "-c1")) {
        FILE *in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w");
        int n;
        fscanf(in, "%d", &n);
        Tree t = createTree();
        for (int c = 0; c < n; c++) {
            char s[20];
            fscanf(in, "%s", s);
            strcat(s, "$");
            t = insert(t, s);
        }
        weirdBFS(out, t);
        t = destroyTree(t);
        fclose(in);
        fclose(out);
        return 0;
    } else if (!strcmp(argv[1], "-c2")) {
        FILE *in = fopen(argv[3], "r");
        FILE *out = fopen(argv[4], "w");
        int k = atoi(argv[2]);
        int n;
        fscanf(in, "%d", &n);
        Tree t = createTree();
        for (int c = 0; c < n; c++) {
            char s[20];
            fscanf(in, "%s", s);
            strcat(s, "$");
            t = insert(t, s);
        }
        fprintf(out, "%d\n%d\n%d\n",
                    countLeaves(t),
                    KLengthSuffix(t, k, 0),
                    mostDescendants(t));
        t = destroyTree(t);
        fclose(in);
        fclose(out);
        return 0;
    } else if (!strcmp(argv[1], "-c3")) {
        FILE* in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w");
        int nrWords, nrSuffix;
        fscanf(in, "%d %d", &nrWords, &nrSuffix);
        Tree t = createTree();
        for (int c = 0; c < nrWords; c++) {
            char s[20];
            fscanf(in, "%s", s);
            strcat(s, "$");
            t = insert(t, s);
        }
        for (int c = 0; c < nrSuffix; c++) {
            char *aux = malloc(MAX_SUFFIX_LEN);
            fscanf(in, "%s", aux);
            fprintf(out, "%d\n", containsSuffix(t, aux));
            free(aux);
        }
        t = destroyTree(t);
        fclose(in);
        fclose(out);
        return 0;
    } else if (!strcmp(argv[1], "-c4")) {
        FILE* in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w");
        int n;
        fscanf(in, "%d", &n);
        Tree t = createTree();
        for (int c = 0; c < n; c++) {
            char s[20];
            fscanf(in, "%s", s);
            strcat(s, "$");
            t = insert(t, s);
        }
        CompTree new_tree = malloc(sizeof(CompNode));
        for (int i = 0; i < 27; i++) {
            if (t->children[i])
                new_tree->children[i] = compressTree(t->children[i]);
        }
        compTreeWeirdBFS(out, new_tree);
        fclose(in);
        fclose(out);
        return 0;
    }
    printf("%s", ERROR);
    return -1;
}
