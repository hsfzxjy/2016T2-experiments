#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "element.h"
#include "status.h"

#define isHead(node) ((node)->prev == NULL)
#define isTail(node) ((node)->next == NULL)

typedef struct Node {
    ElemType element;
    Node *prev, *next;
} Node;

status insertBefore (Node* target, Node* src);

status insertAfter (Node* target, Node* src);

status remove (Node* target);

status initNode (Node** n, float p, int e);

int cmpNode (Node* na, Node* pb);

#endif
