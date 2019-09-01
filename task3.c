#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "task3.h"

void dfsCV(Graph g, int start, int low[], int idx[], int time, List *artPoints)
{
    List tmp = g->adjList[start], children = NULL;

    idx[start] = time;
    low[start] = time;
    g->visited[start] = 1;

    while (tmp != NULL)
    {
        // daca nodul este nedescoperit
        if (g->visited[tmp->v] == 0)
        {
            dfsCV(g, tmp->v, low, idx, time + 1, artPoints);

            // adaugam nodul la copii lui 'start'
            children = addLast(children, tmp->v, 0);

            if (low[tmp->v] < low[start])
            {
                low[start] = low[tmp->v];
            }
        }
        else
        {
            // nodul este descoperit
            // muchia (start, tmp->v) e muchie inapoi
            if (idx[tmp->v] < low[start])
            {
                low[start] = idx[tmp->v];
            }
        }

        tmp = tmp->next;
    }

    tmp = children;
    // daca start e radacina arborelui
    if (low[start] == idx[start])
    {
        int counter = 0;
        // se determina numarul de copii
        while (tmp != NULL)
        {
            counter++;
            tmp = tmp->next;
        }

        // daca sunt 2 sau mai multi copii, start e punct de articulatie
        if (counter > 1)
        {
            (*artPoints) = addLast((*artPoints), start, 0);
        }
    }
    else
    {
        while (tmp != NULL)
        {
            // daca exista cel putin un copil, start e punct de articulatie
            if (low[tmp->v] >= idx[start])
            {
                (*artPoints) = addLast((*artPoints), start, 0);
                break;
            }
            tmp = tmp->next;
        }
    }

    //eliberare memorie pentru lista copiilor
    deleteList(children);
}

void task3Main(Graph g, FILE *out)
{
    int i;

    // idx reprezinta momentul de timp la care este descoperit nodul
    int *idx = (int *)malloc((g->V) * sizeof(int));

    // low reprezinta idx-ul minim al nodurilor dintr-o componenta tare conexa
    int *low = (int *)malloc((g->V) * sizeof(int));

    // lista contine punctele de articulatie
    List artPoints = NULL;

    // se aplica dfs-ul modificat pentru determinarea punctelor de articulatie
    for (i = 1; i < g->V; i++)
    {
        if (g->visited[i] == 0)
        {
            dfsCV(g, i, low, idx, 1, &artPoints);
        }
    }

    int counter = 0;
    List iTmp = artPoints, jTmp;

    // ordonare alfabetica a numelor
    while (iTmp != NULL)
    {
        jTmp = iTmp->next;
        while (jTmp != NULL)
        {
            if (strcmp(g->names[iTmp->v], g->names[jTmp->v]) > 0)
            {
                int aux = iTmp->v;
                iTmp->v = jTmp->v;
                jTmp->v = aux;
            }

            jTmp = jTmp->next;
        }

        counter++;
        iTmp = iTmp->next;
    }

    iTmp = artPoints;

    // scrierea in fisier numarul de nume
    fprintf(out, "%d\n", counter);
    while (iTmp != NULL)
    {
        //scrierea in fisier a numelor
        fprintf(out, "%s\n", g->names[iTmp->v]);
        iTmp = iTmp->next;
    }

    //eliberarea memoriei ocupate de vectori
    free(low);
    free(idx);
    deleteList(artPoints);
}