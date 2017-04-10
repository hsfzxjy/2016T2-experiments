#include "bitree.h"
#include "ioutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 20000
#define next(var) (var = (var + 1) % MAX_NODES)

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

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
    if ((*T)->lchild) (*T)->lchild->parent = *T;
    if ((*T)->rchild) (*T)->rchild->parent = *T;
}

bool _validateBiTreeInput (char* input) {
    int i = strlen(input);

    if (!i || ((i + 1) & i) != 0) {
        printf("Length error!\n");
        return false;
    }

    return true;
}

void initBiTree (BiTree* T) {
    char input[MAX_NODES];

    do {
        scanf("%s", input);
        digest();
    } while (!_validateBiTreeInput(input));

    _initBiTree(T, input, strlen(input));
}

void destroyBiTree (BiTree* T) {
    if (!*T) return;
    destroyBiTree(&(*T)->lchild);
    destroyBiTree(&(*T)->rchild);
    free(*T);
    *T = NULL;
}

void preOrder (BiTree T, BiTreeCallback f) {
    if (!T) return;
    f(T);
    preOrder(T->lchild, f);
    preOrder(T->rchild, f);
}

void postOrder (BiTree T, BiTreeCallback f) {
    if (!T) return;
    postOrder(T->lchild, f);
    postOrder(T->rchild, f);
    f(T);
}

void inOrder (BiTree T, BiTreeCallback f) {
    if (!T) return;
    inOrder(T->lchild, f);
    f(T);
    inOrder(T->rchild, f);
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

    if (T->lchild || T->rchild) {
        println();
        _printBiTree(T->lchild, indent + 1);
        _printBiTree(T->rchild, indent + 1);

        i = indent;
        while (i--) printf("  ");
    }

    printf(")\n");
}

void printBiTree (BiTree T) {
    _printBiTree(T, 0);
}

void printBiNode (BiNode* node) {
    putchar(node ? node->value : '#');
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
    copyBiTree(src->rchild, &(*dest)->rchild);
    if ((*dest)->lchild)
        (*dest)->lchild->parent = *dest;
    if ((*dest)->rchild)
        (*dest)->rchild->parent = *dest;
}

bool _isSortTree (BiTree T, char* min, char* max) {
    if (!T) return true;

    *min = *max = T->value;
    char tmin, tmax;
    bool result = true;

    if (T->lchild) {
        result = _isSortTree(T->lchild, &tmin, &tmax) && tmax <= T->value;
        *min = MIN(*min, tmin);
        *max = MAX(*max, tmax);
    }

    if (T->rchild) {
        result = result && _isSortTree(T->rchild, &tmin, &tmax) && tmin >= T->value;
        *min = MIN(*min, tmin);
        *max = MAX(*max, tmax);
    }

    return result;
}

bool isSortTree (BiTree T) {
    char tmin, tmax;
    return _isSortTree(T, &tmin, &tmax);
}

bool _isBalanceTree (BiTree T, int* h) {
    if (!T) {
        *h = 0;
        return true;
    }

    int lh, rh;
    if (!(_isBalanceTree(T->lchild, &lh) && _isBalanceTree(T->rchild, &rh))) return false;

    *h = (lh > rh ? lh : rh) + 1;
    return abs(lh - rh) <= 1;
}

bool isBalanceTree (BiTree T) {
    int h;
    return _isBalanceTree(T, &h);
}

bool isCompleteTree (BiTree T) {
    if (!T) return true;
    BiNode *Q[MAX_NODES], *node;
    int head = 0, tail = 1; Q[1] = T;
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
    int head = 0, tail = 1; Q[1] = T;

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

BiNode* searchNode (BiTree T, char key) {
    if (!T) return NULL;

    BiNode* node;

    if (T->value == key)
        return T;
    else if (!(node = searchNode(T->lchild, key)))
        node = searchNode(T->rchild, key);

    return node;
}

void _replaceNode (BiNode* node, BiNode* toReplace) {
    if (!node) return;
    BiNode* parent = node->parent;

    if (parent) {
        if (parent->lchild == node) parent->lchild = toReplace; else parent->rchild = toReplace;
    }

    if (toReplace) toReplace->parent = parent;

    destroyBiTree(&node);

}

void deleteNode (BiNode** node) {
    _replaceNode(*node, NULL);
    *node = NULL;
}

void insertBiTree (BiNode** toBeReplaced, BiTree toInsert) {
    _replaceNode(*toBeReplaced, toInsert);
    *toBeReplaced = toInsert;
}

void _printNodeDetails (BiNode* node) {
    if (!node)
        printf("Empty node.\n");
    else
        printf("Node value: %c\n", node->value);
}

void printNodeDetails (BiNode* node) {
    println();
    _printNodeDetails(node);
    if (!node) return;

    printf("Parent: ");
    _printNodeDetails(node->parent);
    printf("Left child: ");
    _printNodeDetails(node->lchild);
    printf("Right child: ");
    _printNodeDetails(node->rchild);
}

void searchNodes (BiTree T, char key, BiTreeCallback f) {
    if (!T) return;
    if (T->value == key) f(T);
    searchNodes(T->lchild, key, f);
    searchNodes(T->rchild, key, f);
}
