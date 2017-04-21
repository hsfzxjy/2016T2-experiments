#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "ioutil.h"

const char* mainMenu =
    "======== MENU ========\n"
    "0) Exit\n"
    "1) Create\n"
    "2) Insert Edge\n"
    "3) Delete Edge\n"
    "4) DFS\n"
    "5) BFS\n"
    "6) Prim\n"
    "7) Shortest Path\n"
    "8) Degrees\n\n";

Graph G;
bool modified = false;
int shortest[26][26] = {0}, path[26][26][26] = {0};

typedef void (*operation)();

void opExit () {
    exit(0);
}

void opCreate () {
    initGraph(&G);
    modified = true;
}

void opInsert () {
    alterEdges(G);
    modified = true;
}

void opDelete () {
    deleteEdges(G);
    modified = true;
}

void print (char c) {
    putchar(c);
}

void opDFS () {
    DFS(G, print);
    printf("\n\n");
}

void opBFS () {
    BFS(G, print);
    printf("\n\n");
}

void opDegrees () {
    printf("Input a vertex: ");
    char v = getLetter();
    printf("Degrees of %c: %d.\n", v, degrees(G, v - 'A'));
}

void opShortestPath () {
    printf("Input v1: ");
    char v1 = getLetter();
    printf("Input v2: ");
    char v2 = getLetter();
    if (modified) shortestPath(G, shortest, path);
    modified = false;
    int d;

    if ((d = shortest[v1 - 'A'][v2 - 'A']) == NOEDGE)
        printf("No path!\n");
    else {
        printf("The shortest path weighs %d.\nThe vertices along side: ", d);
        int i;
        for (i = 0; i < 26; i++) {
            if (path[v1 - 'A'][v2 - 'A'][i]) printf("%c ", i + 'A');
        }
        printf("\n");
    }
}

void opPrim () {
    MSTResult result = prim(G);
    printf("The edges: \n");
    int i;
    for (i = 0; i < result->count; i++)
        printf("%c %c\n", result->edges[i].a + 'A', result->edges[i].b + 'A');
}

operation operations[] = {
    opExit, opCreate, opInsert, opDelete, opDFS, opBFS, opPrim, opShortestPath, opDegrees
};

int cntOperations = sizeof (operations) / sizeof (operation);

int main () {
    while (1) {
        operations[choice(mainMenu, cntOperations)]();
        printf("\n");
    }
    return 0;
}
