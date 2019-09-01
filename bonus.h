#ifndef BONUS
#define BONUS
#include <stdio.h>
#include "graph.h"
#include "binaryTree.h"

Tree removeNodes(Tree root, int value, Graph g);

void generateCliques(Graph g, Tree CS, Tree NOT, Tree CA, Tree *maxClic);

void bonusMain(Graph g, FILE *out);

#endif