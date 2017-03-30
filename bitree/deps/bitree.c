#include "bitree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 20000
#define next(var) (var = (var + 1) % MAX_NODES)

void _initBiTree (BiTree* T, char* input, int len) {
    if (*input == '#') {
        *T = NULL;
        return;
    }
    int half = len >> 1;

    *T = (BiTree) calloc(1, sizeof(BiNode));
    (*T)->value = *input;

    if (len == 1) return;
    _initBiTree(&(*T)->lchild, input + 1, half);
    _initBiTree(&(*T)->rchild, input + 1 + half, half);
    (*T)->lchild->parent = (*T)->rchild->parent = *T;
}

void initBiTree (BiTree* T) {
    char* input[MAX_NODES];
    scanf("%s", input);
    _initBiTree(T, input, strlen(input));
}

void destroyBiTree (BiTree T) {
    if (!T) return;
    destroyBiTree(T->lchild);
    destroyBiTree(T->rchild);
    free(T);
}

void preOrder (BiTree T, BiTreeCallback f) {
    if (!T) return;
    f(T);
    preOrder(T->lchild);
    preOrder(T->rchild);
}

void postOrder (BiTree T, BiTreeCallback f) {
    if (!T) return;
    postOrder(T->lchild);
    postOrder(T->rchild);
    f(T);
}

void inOrder (BiTree T, BiTreeCallback f) {
    if (!T) return;
    inOrder(T->lchild);
    f(T);
    inOrder(T->rchild);
}

int getHeight (BiTree T) {
    if (!T) return 0;
    int lh = getHeight(T->lchild), rh = getHeight(T->rchild);
    return (lh > rh ? lh : rh) + 1;
}

int countLeaves (BiTree T) {
    if (!T) return 0;
    if (!T->lchild && !T->rchild) return 1;
    return countLeaves(T->lchild) + countLeaves(T->rchild);
}

int countNodes (BiTree T) {
    if (!T) return 0;
    return countNodes(T->lchild) + countNodes(T->rchild) + 1;
}

void _printBiTree (BiTree T, int indent) {
    int i = indent;
    while (i--) printf("  ");

    if (!T) {
        printf("()\n");
        return;
    }

    printf("(%c", T->value);
    _printBiTree(T->lchild, indent + 1);
    _printBiTree(T->rchild, indent + 1);
    printf(")\n");
}

void printBiTree (BiTree T) {
    _printBiTree(T, 0);
}

void printBiNode (BiNode*) {
    putchar(BiNode ? BiNode->value : '#');
}

void exchangeLeftRight (BiTree T) {
    if (!T) return;
    exchangeLeftRight(T->lchild);
    exchangeLeftRight(T->rchild);
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
}

void copyBiTree (BiTree src, BiTree* dest) {
    if (!src) return;

    *dest = (BiTree) calloc(1, sizeof(BiNode));
    (*dest)->value = src->value;
    copyBiTree(src->lchild, &(*dest)->lchild);
    copyBiTree(src->rchild, &(*dest)->rchild)
    (*dest)->lchild->parent = (*dest)->rchild->parent = *dest;
}

bool isSortTree (BiTree T) {
    if (!T) return true;

    bool result = (!T->lchild || T->lchild->value <= T->value) && (!T->rchild || T->rchild->value >= T->value);
    return result && isSortTree(T->lchild) && isSortTree(T->rchild);
}

bool _isBalanceTree (BiTree T, int* h) {
    if (!T) {
        *h = 0;
        return true;
    }

    int lh, rh;
    return _isBalanceTree(T->lchild, &lh) && _isBalanceTree(T->rchild, &rh) && abs(lh - rh) <= 1;
}

bool isBalanceTree (BiTree T) {
    int h;
    return _isBalanceTree(T, &h);
}

bool isCompleteTree (BiTree T) {
    if (!T) return true;
    BiNode *Q[MAX_NODES], *node;
    int head = 0; tail = 1; Q[1] = T;
    bool emptyAppeared = false;

    while (head != tail) {
        next(head);
        node = Q[head];

        if (emptyAppeared && (node->lchild || node->rchild)) return false;

        emptyAppeared = !(node->lchild && node->rchild);
        if (node->lchild)
            Q[next(tail)] = node->lchild;
        if (node->rchild)
            Q[next(tail)] = node->rchild;
    }

    return true;
}

void traverseByLayer (BiTree T, BiTreeCallback f) {
    if (!T) return;
    BiNode *Q[10000], *node;
    int head = 0; tail = 1; Q[1] = T;

    while (head != tail) {
        next(head);
        node = Q[head];
        f(node);
        if (node->lchild)
            Q[next(tail)] = node->lchild;
        if (node->rchild)
            Q[next(tail)] = node->rchild;
    }
}
