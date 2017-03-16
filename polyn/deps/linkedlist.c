#include <stdlib.h>

#include "status.h"
#include "linkedlist.h"


status insertBefore (Node* target, Node* src) {
    if (!target || !src || !target->prev) return ERROR;

    Node *prev = target->prev;
    prev->next = src;
    src->prev = prev;
    src->next = target;
    target->prev = src;

    return SUCCESS;
}

status insertAfter (Node* target, Node* src) {
    if (!target || !src) return ERROR;

    Node *next = target->next;
    target->next = src;
    src->prev = target;
    src->next = next;
    if (next) next->prev = src;

    return SUCCESS;
}

status remove (Node* target) {
    if (!target || isHead(target)) return ERROR;

    Node *prev = target->prev;
    target->prev->next = target->next;
    if (target->next) target->next->prev = target->prev;
    free(target);

    return SUCCESS;
}

status initNode (Node** n, float p, int e) {
    *n = (Node*) calloc(1, sizeof(Node));
    if (!*n) return ERROR;
    (*n)->element.e = e;
    (*n)->element.p = p;
    return SUCCESS;
}

int cmpNode (Node* na, Node* pb) {
    return na->element.e - pb->element.e;
}
