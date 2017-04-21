#include <stdio.h>
#include <ctype.h>

void digest () {
    while (getchar() != 10);
}

char getRealChar () {
    char c;
    while (isspace(c = getchar()));
    return c;
}

char getLetter () {
    char c;
    while (!isupper(c = getRealChar())) printf("Invalid!\n");
    return c;
}

int getInt (int max, const char* prompt) {
    int result = -1;
    do {
        printf("%s", prompt);
        fscanf(stdin, "%d", &result);
        digest();
    } while (result <= 0 || result > max);
    return result;
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
