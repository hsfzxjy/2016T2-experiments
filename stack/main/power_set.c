#include <stdio.h>
#include <stdlib.h>

void printSet(bool* set, int n) {
    printf("{ ");
    int i;
    for (i = 0; i < n; i++)
        if (set[i]) printf("%d ", i + 1);
    printf("}\n");
}

void dfs(bool* set, int n, int cur) {
    if (cur >= n) {
        printSet(set, n);
        return;
    }

    int i;
    for (i = 0; i < 2; i++) {
        set[cur] = i;
        dfs(set, n, cur + 1);
    }
}

int main () {
    int n;
    printf("Input n: ");
    scanf("%d", &n);
    bool* set = (bool*) calloc(n, sizeof(bool));

    dfs(set, n, 0);

    free(set);
    return 0;
}
