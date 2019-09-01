#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// initializare stiva
Stack initStack(int value)
{
    Stack new = (Stack)malloc(sizeof(struct stack));
    new->value = value;
    new->next = NULL;

    return new;
}

// adaugare in stiva
Stack push(Stack s, int value)
{
    Stack new = initStack(value);
    new->next = s;

    return new;
}

// extragere din stiva
Stack pop(Stack s)
{
    Stack tmp = s;
    s = s->next;
    free(tmp);

    return s;
}

// returneaza valoarea ce urmeaza din stiva
int top(Stack s)
{
    return s->value;
}

// verifica daca stiva e nula
int isEmptyStack(Stack s)
{
    if (s == NULL)
        return 1;
    return 0;
}