#include "stack.h"

void initStack(Stack* s) {
    *s = (Stack) malloc(sizeof(_Stack));
    if (!*s) raise(OVERFLOW);
    (*s)->store = (Element*) malloc(sizeof(Element) * MAX_STACK_SIZE);
    if (!(*s)->store) raise(OVERFLOW);
    (*s)->size = MAX_STACK_SIZE;
    (*s)->top = 0;
}

void destroyStack(Stack s) {
    free(s->store);
    free(s);
}

void emptyStack(Stack s) {
    s->top = 0;
}

bool isEmpty(Stack s) {
    return !s->top;
}

void push(Stack s, Element e) {
    if (s->top == s->size) raise(OVERFLOW);
    s->store[s->top++] = e;
}

status pop(Stack s, Element* e) {
    if (!s->top) return (ERROR);
    *e = s->store[--s->top];
    return SUCCESS;
}

status getTop(Stack s, Element* e) {
    if (!s->top) return (ERROR);
    *e = s->store[s->top-1];
    return SUCCESS;
}
