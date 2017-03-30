#include <stdio.h>
#include "stack.h"

bool matched (char left, char right) {
    switch (left) {
        case '{': return right == '}';
        case '[': return right == ']';
        case '(': return right == ')';
    }
    return false;
}

int main () {
    char c, top;
    bool success = true;
    Stack s;
    initStack(&s);

    while (!feof(stdin) && (c = getchar()) != '\n') {
        switch (c) {
            case '(': case '{': case '[':
                push(s, c);
                continue;
        }
        if (!pop(s, &top) || !matched(top, c)) {
            success = false;
            break;
        }
    }

    printf("%s\n", success && isEmpty(s) ? "MATCHED" : "MISMATCHED");
    destroyStack(s);

    return 0;
}
