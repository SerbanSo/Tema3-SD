#ifndef HEAP
#define HEAP

typedef struct pair{
    int v;
    unsigned long dist;
} Pair;

typedef struct heap{
    Pair *vector;
    int size;
    int capacity;
} *Heap;

Heap initHeap(int max);

Heap siftDown(Heap h, int index);

Heap insertHeap(Heap h, int v, unsigned long cost);

Pair extractMin(Heap h);

Heap deleteHeap(Heap h);

#endif