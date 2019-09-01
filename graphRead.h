#ifndef GRAPHREAD
#define GRAPHREAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int getNamePosition(Graph g, char *nume);

int isConnection(Graph g, int u, int v);

int maxActors(FILE *file);

Graph readGraphPb1(FILE *file, int V);

List *readPortals(List *patrol, FILE *file, int N);

Graph readGraphPb2(Graph g, FILE *file, int M);

#endif