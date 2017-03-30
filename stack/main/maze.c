#include <stdio.h>
#include <stdlib.h>

#define BLOCK '1'
#define PATH '0'
#define MARK '*'

typedef char** Maze;

const int delta[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

bool walk(Maze maze, int m, int n, int x, int y) {
    if (!(0 <= x && x < m && 0 <= y && y < n && maze[x][y] == PATH)) return false;
    maze[x][y] = MARK;
    if (x == m-1 && y == n-1) return true;

    int i;
    for (i = 0; i < 4; i++)
        if (walk(maze, m, n, x + delta[i][0], y + delta[i][1])) return true;

    maze[x][y] = PATH;
    return false;
}

Maze initMaze (int m, int n) {
    Maze result = (Maze) malloc(sizeof(char*) * m);
    int i;
    for (i = 0; i < n; i++) result[i] = (char*) malloc(sizeof(char) * n);
    return result;
}

int main () {
    int m, n, i, j;
    char c;
    Maze maze;
    printf("Input rows and columns: ");
    scanf("%d%d", &m, &n);
    maze = initMaze(m, n);

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            do {
                c = maze[i][j] = getchar();
            } while (c != BLOCK && c != PATH);

    printf("\n");

    if (walk(maze, m, n, 0, 0))
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) putchar(maze[i][j]);
            putchar('\n');
        }
    else printf("NO SOLUTION!\n");

    return 0;
}
