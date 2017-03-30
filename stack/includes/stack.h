#ifndef _STACK_H_
#define _STACK_H_

#include "status.h"

#define MAX_STACK_SIZE 10000

typedef struct {
    Element *store;
    long size;
    long top;
} _Stack, *Stack;

void initStack(Stack*);
void destroyStack(Stack);
void emptyStack(Stack);
bool isEmpty(Stack);
void push(Stack, Element);
status pop(Stack, Element*);
status getTop(Stack, Element*);

#endif
