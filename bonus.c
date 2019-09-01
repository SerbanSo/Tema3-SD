#include <string.h>
#include "graphRead.h"
#include "bonus.h"

// se elimina nodurile care nu sunt vecine cu nodul "value"
Tree removeNodes(Tree root, int value, Graph g)
{
    if (root != NULL)
    {
        root->left = removeNodes(root->left, value, g);
        root->right = removeNodes(root->right, value, g);

        List tmp = g->adjList[root->id];
        int ok = 0;

        while (tmp != NULL)
        {
            if (tmp->v == value)
            {
                ok = 1;
                break;
            }
            tmp = tmp->next;
        }

        if (ok == 0)
        {
            root = deleteNode(root, root->id);
        }
    }
    return root;
}

// algoritmul de genarat clici
void generateCliques(Graph g, Tree CS, Tree NOT, Tree CA, Tree *maxClic)
{
    List tmp, aux;
    if (CA != NULL)
    {
        int c = CA->id;
        CA = deleteNode(CA, c);
        CS = addNode(CS, c);

        CA = removeNodes(CA, c, g);
        NOT = removeNodes(NOT, c, g);

        generateCliques(g, CS, NOT, CA, maxClic);

        CS = deleteNode(CS, c);
        NOT = addNode(NOT, c);
    }
    else if (NOT == NULL)
    {
        // daca clica maxima se copiaza in maxClic
        if (nodesNumber(CS) > nodesNumber((*maxClic)))
        {
            deleteTree((*maxClic));
            (*maxClic) = copyTree(CS);
        }
    }
}

void bonusMain(Graph g, FILE *out)
{
    List tmp;
    Tree CA = NULL, CS = NULL, NOT = NULL, maxClic = NULL;
    int i, j;

    for (i = 1; i < g->V; i++)
    {
        CA = NULL;
        CS = NULL;
        NOT = NULL;
        tmp = g->adjList[i];

        CA = initNode(i);
        while (tmp != NULL)
        {
            CA = addNode(CA, tmp->v);
            tmp = tmp->next;
        }

        generateCliques(g, CS, NOT, CA, &maxClic);

        deleteTree(CS);
        deleteTree(NOT);
    }

    // se copiaza arborele intr-un vector
    // pentru a se putea ordona alfabetic dupa nume
    int max = nodesNumber(maxClic);
    int *vect = (int *)malloc(max * sizeof(int));

    max = 0;
    copyToVector(maxClic, vect, &max);
    max++;

    //ordonarea alfabetica a numelor
    for (i = 0; i < max; i++)
    {
        for (j = i + 1; j < max; j++)
        {
            if (strcmp(g->names[vect[i]], g->names[vect[j]]) > 0)
            {
                int aux = vect[i];
                vect[i] = vect[j];
                vect[j] = aux;
            }
        }
    }

    //scrierea in fisier a numarului de nume
    fprintf(out, "%d\n", max);
    for (i = 0; i < max; i++)
    {
        //scrierea in fisier a numelor
        fprintf(out, "%s\n", g->names[vect[i]]);
    }

    free(vect);
    deleteTree(maxClic);
}