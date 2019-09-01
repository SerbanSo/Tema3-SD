#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binaryTree.h"

// initializarea arbore binar
Tree initNode(int value)
{
    Tree new = (Tree)malloc(sizeof(struct tree));
    new->id = value;
    new->left = NULL;
    new->right = NULL;

    return new;
}

// adaugare element in arbore binar
Tree addNode(Tree root, int value)
{
    if(root == NULL)
    {
        root = initNode(value);
        return root;
    }
    else
    {
        if(value < root->id)
        {
            root->left = addNode(root->left, value);
        }
        else
        {
            root->right = addNode(root->right, value);
        }
        return root;        
    }
}

// cauta un element in arbore
Tree searchNode(Tree root, int value)
{
    if(root != NULL)
    {
        if(root->id == value)
        {
            return root;
        }
        else
        {
            if(value < root->id)
            {
                return searchNode(root->left, value);
            }
            else
            {
                return searchNode(root->right, value);
            }
        }
    }
    return NULL;
}

// returneaza minimul din arbore
int minID(Tree root)
{
    if(root == NULL)
        return -1;
    while(root->left != NULL)
    {
        root = root->left;
    }
    return root->id;
}


// sterge un element din arbore
Tree deleteNode(Tree root, int value)
{
    if(root == NULL)
    {
        return root;
    }
    if(value < root->id)
    {
        root->left = deleteNode(root->left, value);
    }
    else if(value > root->id)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        if(root->left != NULL && root->right != NULL)
        {
            int min = minID(root->right);
            root->id = min;
            root->right = deleteNode(root->right, min);
        }
        else
        {
            Tree tmp = root;
            if(root->left != NULL)
            {
                root = root->left;
            }
            else
            {
                root = root->right;
            }
            free(tmp);
        }
    }
    return root;    
}

// returneaza numarul de noduri din arbore
int nodesNumber(Tree root)
{
    if(root != NULL)
    {
        return 1 + nodesNumber(root->left) + nodesNumber(root->right);
    } 
    return 0;
}

// copiaza arborele intr-un vector
void copyToVector(Tree root, int vect[], int *i)
{
    if(root != NULL)
    {
        vect[*i] = root->id;
        (*i)++;
        copyToVector(root->left, vect, i);
        (*i)++;
        copyToVector(root->right, vect, i);
    }
    else
    {
        (*i)--;
    }
}

// copiaza arborele dat ca parametru
Tree copyTree(Tree source)
{
    if (source != NULL)
    {
        Tree new = initNode(source->id);

        new->left = copyTree(source->left);
        new->right = copyTree(source->right);

        return new;
    }
    else
    {
        return NULL;
    }
}

// sterge arborele din memorie
void deleteTree(Tree root)
{
    if (root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);

        free(root);
    }
}