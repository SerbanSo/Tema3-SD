#ifndef LIST
#define LIST

typedef struct list
{
    struct list *next;
    int v;
    unsigned long cost;
} * List;

List initList(int v, unsigned long cost);

List addLast(List list, int v, unsigned long cost);

List deleteElement(List list, int v);

List deleteList(List list);

#endif