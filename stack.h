#ifndef STACK
#define STACK

typedef struct stack
{
    struct stack *next;
    int value;
} * Stack;

Stack initStack(int value);

Stack push(Stack s, int value);

Stack pop(Stack s);

int top(Stack s);

int isEmptyStack(Stack s);

#endif