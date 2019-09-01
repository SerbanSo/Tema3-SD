#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "heap.h"
#define INF 999999
#define MAX 100

// initializarea grafului
Graph initGraph(int max)
{
    Graph new = (Graph)malloc(sizeof(struct graph));
    int i;

    new->max = max;
    new->adjList = (List *)malloc((max + 1) * sizeof(List));
    new->visited = (int *)calloc(max + 1, sizeof(int));
    new->names = (char **)malloc((max + 1) * sizeof(char *));

    //initializare matrice cu NULL
    for (i = 0; i <= max; i++)
    {
        new->adjList[i] = NULL;
        new->names[i] = NULL;
    }

    new->V = 1;

    return new;
}

// inserarea de muchii in graf
Graph insertEdge(Graph g, int u, int v, unsigned long cost)
{
    g->adjList[u] = addLast(g->adjList[u], v, cost);
    g->adjList[v] = addLast(g->adjList[v], u, cost);

    return g;
}

// depth first search
void dfs(Graph g, int start)
{
    List tmp = g->adjList[start];

    g->visited[start] = 1;
    while (tmp != NULL)
    {
        if (g->visited[tmp->v] == 0)
        {
            dfs(g, tmp->v);
        }

        tmp = tmp->next;
    }
}

// numara cate elemente conexe sunt in graf
int connectedComponents(Graph g)
{
    int i, counter = 0;

    for (i = 1; i < g->V; i++)
    {
        if (g->visited[i] == 0)
        {
            counter++;
            dfs(g, i);
        }
    }

    return counter;
}

// calculul distantei minime pornind de la un punct
int minDistance(Graph g, int start, int end)
{
    // alocare vector de costuri
    int *cost = (int *)malloc((g->V + 1) * sizeof(int));
    int i;
    Heap h = initHeap(g->V);

    // initializare vector cu INF
    for (i = 1; i < g->V; i++)
    {
        cost[i] = INF;
    }

    //initializare vector cu valorile din start
    List tmp = g->adjList[start];

    while (tmp != NULL)
    {
        cost[tmp->v] = 1;
        h = insertHeap(h, tmp->v, 1);

        tmp = tmp->next;
    }

    // dijsktra - implementare cu heap
    g->visited[start] = 1;
    int j;
    int min, index;
    while (h->size != 0)
    {
        index = extractMin(h).v;
        while (g->visited[index] == 1)
        {
            index = extractMin(h).v;
        }

        g->visited[index] = 1;
        tmp = g->adjList[index];

        //actualizarea distantelor intre 2 noduri, daca este cazul
        while (tmp != NULL)
        {
            if (g->visited[tmp->v] == 0)
            {
                if (1 + cost[index] < cost[tmp->v])
                {
                    cost[tmp->v] = 1 + cost[index];
                    h = insertHeap(h, tmp->v, cost[tmp->v]);
                }
            }
            tmp = tmp->next;
        }
    }

    min = cost[end];
    free(cost);
    deleteHeap(h);

    if (min == INF)
        return 0;
    return min;
}

// stergerea grafului din memorie
Graph deleteGraph(Graph g)
{
    int i;

    free(g->visited);

    for (i = 0; i < g->max; i++)
    {
        g->adjList[i] = deleteList(g->adjList[i]);
    }
    free(g->adjList);

    for (i = 0; i < g->max; i++)
    {
        free(g->names[i]);
    }
    free(g->names);

    free(g);
    return g;
}