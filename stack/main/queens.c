#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int* Board;

void printBoard(Board b, int n) {
    int i, j;
    putchar('\n');
    for (i = 0; i < n; i++) {
        for (j = 0; j < b[i]; j++) putchar('*');
        putchar('o');
        for (j++; j < n; j++) putchar('*');
        putchar('\n');
    }
}

bool check (Board b, int m) {
    int i, j;

    for (i = 0; i < m; i++)
        for (j = i + 1; j < m; j++)
            if (abs(i - j) == abs(b[i] - b[j])) return false;

    return true;
}

void dfs (Board b, int n, int current, bool* used) {
    if (current >= n) {
        printBoard(b, n);
        return;
    }
    int i;

    for (i = 0; i < n; i++)
        if (!used[i]) {
            b[current] = i;
            if (!check(b, current + 1)) continue;
            used[i] = true;
            dfs(b, n, current + 1, used);
            used[i] = false;
        }
}

int main () {
    int n;
    printf("Input n: ");
    scanf("%d", &n);
    Board board = (Board) calloc(n, sizeof(int));
    bool* used = (bool*) calloc(n, sizeof(bool));

    dfs(board, n, 0, used);

    free(board);
    free(used);
    return 0;
}
