#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// initializare heap
Heap initHeap(int max)
{
    Heap new = (Heap)malloc(sizeof(struct heap));
    new->vector = (Pair *)malloc((max) * sizeof(Pair));
    new->capacity = max;
    new->size = 0;

    return new;
}

// aranjeaza heap-ul
Heap siftDown(Heap h, int index)
{
    int left = index * 2 + 1;
    int right = left + 1;
    int small = index;
    unsigned long value = h->vector[index].dist;

    if (left < h->size && h->vector[left].dist < h->vector[index].dist)
    {
        small = left;
    }
    if (right < h->size && h->vector[right].dist < h->vector[small].dist)
    {
        small = right;
    }

    if (small != index)
    {
        Pair tmp = h->vector[index];
        h->vector[index] = h->vector[small];
        h->vector[small] = tmp;

        h = siftDown(h, small);
    }

    return h;
}

// insereaza in heap
Heap insertHeap(Heap h, int v, unsigned long cost)
{
    h->vector[h->size].dist = cost;
    h->vector[h->size].v = v;
    int index = h->size;

    while (index != 0 && h->vector[index].dist < h->vector[index / 2].dist)
    {
        Pair tmp = h->vector[index / 2];
        h->vector[index / 2] = h->vector[index];
        h->vector[index] = tmp;

        index = index / 2;
    }

    h->size++;

    return h;
}

// extrage minimul din heap
Pair extractMin(Heap h)
{
    if (h->size == 1)
    {
        h->size--;
        return h->vector[0];
    }

    Pair min = h->vector[0];
    h->size--;
    h->vector[0] = h->vector[h->size];
    h = siftDown(h, 0);

    return min;
}


// sterge heap-ul din memorie
Heap deleteHeap(Heap h)
{
    free(h->vector);
    free(h);

    return h;
}