#include <stdio.h>
#include "graph.h"
#include "ioutil.h"
#include <ctype.h>
#include <stdlib.h>

#define QMAX 100
#define QNEXT(var) (var = (var + 1) % QMAX)

void fill2DArray (int matrix[26][26], int value) {
    int i, j;
    for (i = 0; i < 26; i++)
        for (j = 0; j < 26; j++)
            matrix[i][j] = value;
}

void fill3DArray (int matrix[26][26][26], int value) {
    int i, j, k;
    for (i = 0; i < 26; i++)
        for (j = 0; j < 26; j++)
            for (k = 0; k < 26; k++)
                matrix[i][j][k] = value;
}

void initGraph (Graph* G) {
    int nodes, w;
    char c;
    *G = (Graph) calloc(1, sizeof(TGraph));
    (*G)->vexcount = nodes = getInt(26, "Please enter the number of nodes (no more than 26) ");
    printf("Input nodes: ");
    while (nodes--) {
        while (!isupper(c = getRealChar()));
        (*G)->vertices[(*G)->vexcount - nodes - 1] = c - 'A';
    }
    fill2DArray((*G)->matrix, INF);
    alterEdges(*G);
}

bool getVertexPair (char* c1, char* c2) {
    while (1) {
        printf("Enter edge (`#` to pass) ");
        *c1 = getRealChar();
        if (*c1 == '#') return false;
        *c2 = getRealChar();
        if (isupper(*c1) && isupper(*c2)) return true;
        printf("Invalid!\n");
        digest();
    }
}

void alterEdge (Graph G, char c1, char c2, int weight) {
    G->matrix[c1 - 'A'][c2 - 'A'] = G->matrix[c2 - 'A'][c1 - 'A'] = weight;
}

void alterEdges (Graph G) {
    char c1, c2;
    printf("Input edges: \n");
    while (1) {
        if (!getVertexPair(&c1, &c2)) return;
        int w = 1;
        printf("Input weight: ");
        scanf("%d", &w);
        alterEdge(G, c1, c2, w);
    }
}

void deleteEdges (Graph G) {
    char c1, c2;
    printf("Input edges: \n");
    while (1) {
        if (!getVertexPair(&c1, &c2)) return;
        alterEdge(G, c1, c2, INF);
    }
}

void _DFS (Graph G, int vertex, bool* visited, GraphCallback cb) {
    int i;
    cb(vertex + 'A');
    visited[vertex] = true;

    for (i = 0; i < 26; i++)
        if (G->matrix[vertex][i] != NOEDGE && !visited[i])
            _DFS(G, i, visited, cb);
}

void DFS (Graph G, GraphCallback cb) {
    bool visited[26] = {0};
    _DFS(G, G->vertices[0], visited, cb);

}

void BFS (Graph G, GraphCallback cb) {
    bool visited[26] = {0};
    int queue[QMAX], head = 0, tail = 1, i, v1, v2;
    queue[1] = G->vertices[0];
    visited[G->vertices[0]] = true;

    while (head != tail) {
        QNEXT(head);
        v1 = queue[head];
        cb(v1 + 'A');
        for (i = 0; i < 26; i++)
            if (!visited[i] && G->matrix[v1][i] != NOEDGE) {
                // printf("\n%c--%c\n", v1 + 'A', i + 'A');
                visited[i] = true;
                QNEXT(tail);
                queue[tail] = i;
            }
    }
}

int degrees (Graph G, int v) {
    int result = 0, i;
    for (i = 0; i < 26; i++) result += G->matrix[v][i] != NOEDGE;
    return result;
}

void shortestPath (Graph G, int store[26][26], int paths[26][26][26]) {
    fill2DArray(store, INF);
   // fill3DArray(paths, 0);
    int i, j, k, l, u, v, w, x;

    for (i = 0; i < G->vexcount; i++)
        for (j = 0; j < G->vexcount; j++) {
            v = G->vertices[i], w = G->vertices[j];
            store[v][w] = G->matrix[v][w];

            for (k = 0; k < G->vexcount; k++) {
                u = G->vertices[k];
                paths[v][w][u] = false;
            }

            if (store[v][w] < INF) {
                paths[v][w][v] = paths[v][w][w] = true;
            }
        }

    for (i = 0; i < G->vexcount; i++)
        for (j = 0; j < G->vexcount; j++)
            for (k = 0; k < G->vexcount; k++) {
                u = G->vertices[i], v = G->vertices[j], w = G->vertices[k];
                if (store[v][u] + store[u][w] < store[v][w]) {
                    store[v][w] = store[v][u] + store[u][w];

                    for (l = 0; l < G->vexcount; l++) {
                        x = G->vertices[l];
                        paths[v][w][x] = paths[v][u][x] || paths[u][w][x];
                    }
                }
            }
}

MSTResult prim (Graph G) {
    struct {
        int adjvex;
        int lowest;
    } closest[26] = {0};

    MSTResult result = (MSTResult) calloc(1, sizeof(TMSTResult));
    result->count = G->vexcount - 1;

    int i, j, u = G->vertices[0], v, k, mincost;
    for (j = 0; j < G->vexcount; j++) {
        v = G->vertices[j];
        if (u != v) closest[j].adjvex = u, closest[j].lowest = G->matrix[u][v];
    }
    closest[0].lowest = 0;

    for (i = 0; i < G->vexcount - 1; i++) {
        k = 0; mincost = INF;
        for (j = 0; j < G->vexcount; j++)
            if (closest[j].lowest && mincost > closest[j].lowest) {
                k = j;
                mincost = closest[j].lowest;
            }
        // int ii;
        // for (ii = 0; ii < G->vexcount; ii++)
        //     printf("%d: %d, %d\n", ii, closest[ii].adjvex, closest[ii].lowest);
        // printf("----%d\n", k);
        result->edges[i].a = closest[k].adjvex;
        result->edges[i].b = G->vertices[k];

        closest[k].lowest = 0;
        for (j = 0; j < G->vexcount; j++) {
            if (G->matrix[G->vertices[k]][G->vertices[j]] < closest[j].lowest) {
                closest[j].adjvex = G->vertices[k];
                closest[j].lowest = G->matrix[G->vertices[k]][G->vertices[j]];
            }
        }
    }

    return result;
}
