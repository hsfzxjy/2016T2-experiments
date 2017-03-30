#include <stdio.h>

#include "status.h"
#include "stack.h"

double calculate (double num1, char op, double num2) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2) return num1 * 1.0 / num2; else raise(DIVIDED_BY_ZERO);
    }
    raise(ERROR);
}

int main () {
    char c;
    Stack s;
    bool success = true;
    double n1, n2;
    initStack(&s);

    while (!feof(stdin) && (c = getchar()) != '\n') {
        if (c == ' ' || c == '\t')
            continue;
        else if ('0' <= c && c <= '9')
            push(s, c - '0');
        else if (pop(s, &n2) && pop(s, &n1))
            push(s, calculate(n1, c, n2));
        else {
            success = false;
            break;
        }
    }

    if (success)
        printf("Result: %lf\n", getTop(s, &n1) ? n1 : 0);
    else
        printf("ERROR\n");

    return 0;
}
