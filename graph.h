#ifndef GRAPH
#define GRAPH
#include <stdio.h>
#include "list.h"

typedef struct graph
{
    int max;
    int V;
    int *visited;
    char **names;
    List *adjList;
} * Graph;

Graph initGraph(int V);

Graph insertEdge(Graph g, int u, int v, unsigned long cost);

void printGraph(Graph g);

void dfs(Graph g, int start);

void resetViz(Graph g);

int connectedComponents(Graph g);

int minDistance(Graph g, int start, int end);

Graph deleteGraph(Graph g);

#endif