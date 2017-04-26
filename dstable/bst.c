#include <stdio.h>
#include <stdlib.h>

#define DEBUG(x) do {\
    printf(x);\
    fflush(stdout);\
} while (0)

typedef struct _Node {
    int value;
    _Node* lchild;
    _Node* rchild;
    _Node* parent;
} TBSTNode, *BSTNode, *BST;

void destroyBST (BST* T) {
    if (!*T) return;
    destroyBST(&(*T)->lchild);
    destroyBST(&(*T)->rchild);
    free(*T);
    *T = NULL;
}

void _insertBST (BST* T, int value, BSTNode p) {
    if (!*T) {
        *T = (BST) calloc(1, sizeof(TBSTNode));
        (*T)->value = value;
        (*T)->parent = p;
        return;
    }
    BST bst = *T;
    if (value < bst->value) _insertBST(&bst->lchild, value, bst);
    if (value > bst->value) _insertBST(&bst->rchild, value, bst);
}

void insertBST (BST* T, int value) {
    _insertBST(T, value, NULL);
}

BSTNode searchBST (BST T, int value) {
    if (!T) return NULL;
    if (T->value == value) return T;
    return searchBST(T->value > value ? T->lchild : T->rchild, value);
}

int _countChildren (BSTNode T) {
    int cnt = 0;
    if (T->lchild) cnt++;
    if (T->rchild) cnt++;
    return cnt;
}

void _safeSet (BSTNode T, BSTNode newNode, BSTNode* root) {
    if (!T->parent) {
        *root = newNode;
        return;
    }

    BSTNode* ref;
    if (T->parent->lchild == T)
        ref = &(T->parent->lchild);
    else
        ref = &(T->parent->rchild);
    *ref = newNode;
}

void deleteBST (BST *T, int value) {
    BSTNode node = searchBST(*T, value), c, p;
    if (!node) return;
    switch (_countChildren(node)) {
        case 0:
            _safeSet(node, NULL, T);
            free(node);
            break;
        case 1:
            c = (node->lchild) ? node->lchild : node->rchild;
            _safeSet(node, c, T);
            free(node);
            break;
        case 2:
            p = node->rchild;
            for (; _countChildren(p); p = p->lchild);
            node->value = p->value;
            _safeSet(p, NULL, T);
            free(p);
    }
}

BST tree = NULL;

const char* menu =
    "======= BST MENU =======\n"
    "0) Exit\n"
    "1) Insert\n"
    "2) Delete\n"
    "3) Search\n";

void digest (void) {
    while (getchar() != 10);
}

int choice (const char* menu, int num) {
    int result = -1;

    do {
        printf("%s\nMake a choice (0 ~ %d) ", menu, num - 1);
        scanf("%d", &result);
        printf("\n");
        digest();
    } while (result < 0 || result >= num);

    return result;
}

typedef void (*Operation)();

void opExit () {
    exit(0);
}

void opInsert () {
    int value = -1;
    do {
        printf("Enter an positive integer (-1 to pass) ");
        scanf("%d", &value);
        if (value == -1) break;
        insertBST(&tree, value);
    } while (1);
}

void opDelete () {
    int value = -1;
    do {
        printf("Enter an positive integer (-1 to pass) ");
        scanf("%d", &value);
        if (value == -1) break;
        deleteBST(&tree, value);
    } while (1);
}

void opSearch () {
    int value;
    printf("Input value to be searched: ");
    scanf("%d", &value);
    printf("Result: %s.", searchBST(tree, value) ? "TRUE" : "FALSE");
}

Operation operations[] = { opExit, opInsert, opDelete, opSearch };
int nOperations = sizeof(operations) / sizeof(Operation);

int main () {
    while (1) {
        operations[choice(menu, nOperations)]();
        printf("\n");
    }
    destroyBST(&tree);
    return 0;
}
