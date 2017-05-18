#include <stdio.h>
#include <stdlib.h>

#include "ioutil.h"
#include "polyn.h"

typedef void (*Operation)();

const char* mainMenu =
    "==== MENU ====\n"
    "0) create\n"
    "1) add\n"
    "2) substract\n"
    "3) print\n"
    "4) eval\n"
    "5) differentiate\n"
    "6) integrate\n"
    "7) multiply\n"
    "8) divide\n"
    "9) exit\n\n";

Polyn pa = NULL, pb = NULL;

void inputPolyn (const char* prompt, Polyn* p) {
    destroyPolyn(p);
    printf("%s\n", prompt);
    createPolyn(p, getPositiveInt("Input m: "));
}

void opCreate () {
    inputPolyn("Input Polyn A: ", &pa);
    inputPolyn("Input Polyn B: ", &pb);
}

void opPrint () {
    printf("Polyn A: ");
    printPolyn(pa);
    printf("Polyn B: ");
    printPolyn(pb);
}

void opAdd () {
    Polyn result;
    initPolyn(&result);
    opPrint();
    if (addPolyn(pa, pb, &result)) {
        printf("Result of A+B: ");
        printPolyn(result);
    } else {
        printf("ERROR!\n");
    }
    destroyPolyn(&result);
}

void opSubstract () {
    Polyn result;
    initPolyn(&result);
    opPrint();
    if (substractPolyn(pa, pb, &result)) {
        printf("Result: ");
        printPolyn(result);
    } else {
        printf("ERROR!\n");
    }
    destroyPolyn(&result);
}

void opEval () {
    Polyn p = NULL;
    double x = 0;

    inputPolyn("Input Polyn: ", &p);
    printf("Polyn to evaluate: ");
    printPolyn(p);
    printf("Input x: ");
    scanf("%lf", &x);
    printf("Result: %lg\n", evalPolyn(p, x));
    destroyPolyn(&p);
}

void opDiff () {
    Polyn p = NULL, result;

    inputPolyn("Input Polyn to differentiate: ", &p);
    printf("You've entered: ");
    printPolyn(p);
    initPolyn(&result);
    diffPolyn(p, &result);
    printf("Result: ");
    printPolyn(result);

    destroyPolyn(&p);
    destroyPolyn(&result);
}

void opInt () {
    Polyn p = NULL, result;

    inputPolyn("Input Polyn to integrate: ", &p);
    printf("You've entered: ");
    printPolyn(p);
    initPolyn(&result);
    intPolyn(p, &result);
    printf("Result: ");
    printPolyn(result);

    destroyPolyn(&p);
    destroyPolyn(&result);
}

void opMul () {
    Polyn result;
    initPolyn(&result);
    opPrint();
    if (mulPolyn(pa, pb, &result)) {
        printf("Result of A*B: ");
        printPolyn(result);
    } else printf("ERROR!\n");

    destroyPolyn(&result);
}

void opDiv () {
    Polyn div = NULL, mod = NULL;
    opPrint();

    if (divmodPolyn(pa, pb, &div, &mod)) {
        printf("Result of A/B:\nDiv part: ");
        printPolyn(div);
        printf("Mod part: ");
        printPolyn(mod);
    } else printf("ERROR!\n");

    destroyPolyn(&div);
    destroyPolyn(&mod);
}

void opExit () {
    exit(0);
}

Operation operations[] = {
    opCreate, opAdd, opSubstract, opPrint, opEval, opDiff, opInt, opMul, opDiv, opExit
};

const int ITEMS_N = sizeof(operations) / sizeof(Operation);

int main () {
    while (1) {
        operations[choice(mainMenu, ITEMS_N-1)]();
        printf("\n");
    }
    return 0;
}
