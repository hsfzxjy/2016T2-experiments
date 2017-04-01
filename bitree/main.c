#include <stdio.h>
#include <stdlib.h>
#include "bitree.h"
#include "ioutil.h"

const char mainMenu[] =
    "======= MENU =======\n"
    "0) Exit\n"
    "1) Create\n"
    "2) Destroy\n"
    "3) Pre, in, post order traverses\n"
    "4) Print\n"
    "5) Info\n"
    "6) Layer traverse\n"
    "7) Search\n"
    "8) Identify\n"
    "9) Exchange left and right\n"
    "10) Copy\n"
    "11) Delete\n"
    "12) Insert\n";

typedef void (*Operation)();

BiTree tree = NULL;

void opCreate () {
    destroyBiTree(&tree);
    initBiTree(&tree);
    printBiTree(tree);
}

void opDestroy () {
    destroyBiTree(&tree);
}

void opTraverses () {
    printf("Pre order: ");
    preOrder(tree, printBiNode);
    printf("\nIn order: ");
    inOrder(tree, printBiNode);
    printf("\nPost order: ");
    postOrder(tree, printBiNode);
}

void opPrint () {
    printf("Current tree: \n");
    printBiTree(tree);
}

void opInfo () {
    printf("Nodes: %d\nLeaves: %d\nHeight: %d\n", countNodes(tree), countLeaves(tree), getHeight(tree));
}

void opLayerTraverse () {
    printf("Layer order: ");
    traverseByLayer(tree, printBiNode);
    println();
}

void opSearch () {
    char key = inputChar("Input the value to search: ");
    searchNodes(tree, key, printNodeDetails);
}

void opIdentify () {
    opPrint();
    printf(
        "Is sort tree: %s\n"
        "Is balance tree: %s\n"
        "Is complete tree: %s\n",
        btos(isSortTree(tree)),
        btos(isBalanceTree(tree)),
        btos(isCompleteTree(tree))
    );
}

void opExchange () {
    printf("Before:\n");
    printBiTree(tree);
    exchangeLeftRight(tree);
    printf("After:\n");
    printBiTree(tree);
}

void opCopy () {
    BiTree newTree;
    copyBiTree(tree, &newTree);
    printf("New tree: \n");
    printBiTree(newTree);
}

void opDelete () {
    opPrint();
    BiNode* node = searchNode(tree, inputChar("Input the value: "));
    deleteNode(&node);
    opPrint();
}

void opInsert () {
    opPrint();
    BiNode* node = NULL;

    do {
        node = searchNode(tree, inputChar("Input the value: "));

        if (!node)
            printf("Nodes not found!\n");
        else
            break;
    } while (true);

    BiTree t = NULL;
    initBiTree(&t);

    insertBiTree(&node, t);
    opPrint();
}

void opExit () {
    exit(0);
}

#define OPNUMS 13

Operation operations[OPNUMS] = {
    opExit, opCreate, opDestroy, opTraverses,
    opPrint, opInfo, opLayerTraverse, opSearch, opIdentify,
    opExchange, opCopy, opDelete, opInsert
};

int main (void) {
    while (true) {
        operations[choice(mainMenu, OPNUMS)]();
        println();
    }
    return 0;
}
