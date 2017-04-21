#ifndef _GRAPH_H_
#define _GRAPH_H_

#define INF (1<<15)
#define NOEDGE INF

typedef struct {
    int matrix[26][26];
    int vertices[26];
    int vexcount;
} TGraph, *Graph;

typedef struct {
    struct {
        int a;
        int b;
    } edges[26];
    int count;
} TMSTResult, *MSTResult;

typedef void (*GraphCallback)(char);

void initGraph(Graph*);
void DFS(Graph, GraphCallback);
void BFS (Graph, GraphCallback);
int degrees (Graph, int);
void alterEdges(Graph);
void deleteEdges(Graph);
void shortestPath(Graph, int(*)[26], int(*)[26][26]);
MSTResult prim(Graph);

#endif
