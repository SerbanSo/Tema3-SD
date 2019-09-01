#ifndef BTREE
#define BTREE

typedef struct tree
{
    struct tree *left;
    struct tree *right;
    int id;
}*Tree;

Tree initNode(int value);

Tree addNode(Tree root, int value);

Tree searchNode(Tree root, int value);

int minID(Tree root);

Tree deleteNode(Tree root, int value);

int nodesNumber(Tree root);

void copyToVector(Tree root, int vect[], int *i);

Tree copyTree(Tree source);

void deleteTree(Tree root);

#endif