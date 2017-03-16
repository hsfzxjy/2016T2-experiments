#include <stdio.h>
#include "mathutil.h"

void flush () {
    while (getchar() != 10);
}

void smartPrintFloat (float x, bool sign, bool hideOne, bool hideZero) {
    float absx = fabs(x);
    if (x < 0) printf("-");
    if (sign && x > 0) printf("+");
    if (!((isZero(absx) && hideZero) || (absx == 1 && hideOne))) printf("%g", absx);
}

int choice (const char* menu, int max) {
    int choice;
    do {
        choice = -1;
        printf("%sMake a choice (0~%d) ", menu, max);
        scanf("%d", &choice);
        printf("\n");
        flush();
    } while (choice < 0 || choice > max);
    return choice;
}

int getPositiveInt (const char* prompt) {
    int result;
    do {
        result = -1;
        printf("%s", prompt);
        scanf("%d", &result);
        flush();
    } while (result < 0);

    return result;
}
