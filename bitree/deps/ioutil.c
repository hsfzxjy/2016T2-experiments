#include <stdio.h>

void digest (void) {
    while (getchar() != 10);
}

void println (void) {
    printf("\n");
}

int choice (const char* menu, int num) {
    int result = -1;

    do {
        printf("%s\nMake a choice (0 ~ %d) ", menu, num - 1);
        scanf("%d", &result);
        println();
        digest();
    } while (result < 0 || result >= num);

    return result;
}

int inputChar (const char* menu) {
    char result;

    printf("%s ", menu);
    scanf("%c", &result);
    println();
    digest();

    return result;
}

const char* btos (bool b) {
    return b ? "true" : "false";
}
