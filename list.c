#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// initializare lista
List initList(int v, unsigned long cost)
{
    List new = (List)malloc(sizeof(struct list));

    new->v = v;
    new->cost = cost;
    new->next = NULL;

    return new;
}

// adaugare la sfarsitul listei
List addLast(List list, int v, unsigned long cost)
{
    List new = initList(v, cost), tmp = list;

    if (list == NULL)
    {
        return new;
    }

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new;

    return list;
}

// sterge un element specificat din lista
List deleteElement(List list, int v)
{
    List tmp = list, aux = list;

    if (list == NULL)
    {
        return list;
    }
    tmp = tmp->next;

    if (aux->v == v)
    {
        return tmp;
    }

    while (tmp != NULL && tmp->v != v)
    {
        aux = tmp;
        tmp = tmp->next;
    }

    if (tmp->v == v)
        aux->next = tmp->next;

    return list;
}

List deleteList(List list)
{
    List aux;

    while (list != NULL)
    {
        aux = list;
        list = list->next;
        free(aux);
    }

    return list;
}