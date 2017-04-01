#ifndef _BITREE_H_
#define _BITREE_H_

typedef struct Node {
    char value;
    Node *lchild, *rchild, *parent;
} BiNode, *BiTree;

typedef void (*BiTreeCallback)(BiNode*);

void initBiTree(BiTree*);
void destroyBiTree(BiTree*);
void preOrder(BiTree, BiTreeCallback);
void inOrder(BiTree, BiTreeCallback);
void postOrder(BiTree, BiTreeCallback);
void traverseByLayer(BiTree, BiTreeCallback);
BiNode* searchNode(BiTree, char);
void searchNodes(BiTree, char, BiTreeCallback);
int getHeight(BiTree);
int countLeaves(BiTree);
int countNodes(BiTree);
void printBiTree(BiTree);
void printBiNode(BiNode*);
void exchangeLeftRight(BiTree);
void copyBiTree(BiTree, BiTree*);
void insertBiTree(BiNode**, BiTree);
void deleteNode(BiNode**);
void printNodeDetails(BiNode*);
bool isSortTree(BiTree);
bool isBalanceTree(BiTree);
bool isCompleteTree(BiTree);

#endif
