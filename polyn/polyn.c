#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Math Util

#define EPSILON 1e-4
#define isZero(x) (fabs(x)<=EPSILON)

// IO Util

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

// Types & Constants

#define INVALID_E -1
#define SUCCESS 1
#define ERROR 0

typedef int status;
typedef void (*Operation)();

typedef struct {
    float p;
    int e;
} ElemType;

typedef struct Node {
    ElemType element;
    Node *prev, *next;
} Node, *Polyn;

// Linked List Functionalities

#define isHead(node) ((node)->prev == NULL)
#define isTail(node) ((node)->next == NULL)

status insertBefore (Node* target, Node* src) {
    if (!target || !src || !target->prev) return ERROR;

    Node *prev = target->prev;
    prev->next = src;
    src->prev = prev;
    src->next = target;
    target->prev = src;

    return SUCCESS;
}

status insertAfter (Node* target, Node* src) {
    if (!target || !src) return ERROR;

    Node *next = target->next;
    target->next = src;
    src->prev = target;
    src->next = next;
    if (next) next->prev = src;

    return SUCCESS;
}

// Dispose `target`

status remove (Node* target) {
    if (!target || isHead(target)) return ERROR;

    Node *prev = target->prev;
    target->prev->next = target->next;
    if (target->next) target->next->prev = target->prev;
    free(target);

    return SUCCESS;
}

status initNode (Node** n, float p, int e) {
    *n = (Node*) calloc(1, sizeof(Node));
    if (!*n) return ERROR;
    (*n)->element.e = e;
    (*n)->element.p = p;
    return SUCCESS;
}

int cmpNode (Node* na, Node* pb) {
    return na->element.e - pb->element.e;
}

// Polyn Functionalities

status initPolyn(Polyn*);

bool isZeroPolyn (Polyn p) {
    if (!p || !p->next) return true;
    return p->next->element.e == 0 && isZero(p->next->element.p);
}

void clonePolyn (Polyn src, Polyn* target) {
    Node* n, *cur;
    initPolyn(target);
    cur = *target;
    for (src = src->next; src; src = src->next) {
        initNode(&n, src->element.p, src->element.e);
        insertAfter(cur, n);
        cur = n;
    }
}

int cmpPolyn (Polyn pa, Polyn pb) {
    int da = pa && pa->next ? pa->next->element.e : 0;
    int db = pb && pb->next ? pb->next->element.e : 0;
    return da - db;
}

void normalizePolyn (Polyn p) {
    Node* q, *old;
    old = p;
    for (p = p->next; p; p = q) {
        q = p->next;
        if (isZero(p->element.p) && p->element.e) remove(p);
    }
    if (!old->next) {
        initNode(&q, 0, 0);
        insertAfter(old, q);
    }
}

status initPolyn (Polyn* list) {
    return initNode(list, 0, INVALID_E);
}

status destroyPolyn (Polyn* list) {
    Node *p = *list, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    *list = NULL;
    return SUCCESS;
}

void createPolyn (Polyn* p, int m) {
    bool wrong;
    int n, te;
    float tp;
    Node *current, *next;

    do {
        wrong = false;
        n = m;
        printf("Input %d pairs of <p, e>:\n", m);

        initPolyn(p);
        current = *p;
        while (n--) {
            te = tp = 0;
            scanf("%f%d", &tp, &te);

            if (te < 0 || !isHead(current) && current->element.e <= te) {
                wrong = true;
                printf("Error occured!\n");
                destroyPolyn(p);
                flush();
                break;
            }

            initNode(&next, tp, te);
            insertAfter(current, next);
            current = next;
        }
    } while (wrong);

    normalizePolyn(*p);
}

status _addPolyn (Polyn pa, Polyn pb, Polyn* result, int sign) { // Result init by user
    if (!pa || !pb || !result) return ERROR;
    initPolyn(result);

    Node *acurrent = pa->next, *bcurrent = pb->next, *current = *result, *p;
    float sum;

    while (acurrent || bcurrent) {
        if (acurrent && bcurrent && cmpNode(acurrent, bcurrent) == 0) {
            sum = acurrent->element.p + bcurrent->element.p * sign;

            initNode(&p, sum, acurrent->element.e);
            insertAfter(current, p);

            acurrent = acurrent->next;
            bcurrent = bcurrent->next;
        } else if (!bcurrent || acurrent && bcurrent && cmpNode(acurrent, bcurrent) > 0) {
            initNode(&p, acurrent->element.p, acurrent->element.e);
            insertAfter(current, p);

            acurrent = acurrent->next;
        } else {
            initNode(&p, bcurrent->element.p * sign, bcurrent->element.e);
            insertAfter(current, p);

            bcurrent = bcurrent->next;
        }
        current = p;
    }
    normalizePolyn(*result);

    return SUCCESS;
}

status addPolyn (Polyn pa, Polyn pb, Polyn* result) {
    return _addPolyn(pa, pb, result, 1);
}

status substractPolyn (Polyn pa, Polyn pb, Polyn* result) {
    return _addPolyn(pa, pb, result, -1);
}

status printPolyn (Polyn p) {
    if (!p) return ERROR;
    bool first = true;
    int e;

    for (p = p->next; p; p = p->next, first = false) {
        e = p->element.e;
        smartPrintFloat(p->element.p, !first, e, e);
        printf(!e ? "" : e == 1 ? "x" : "x^");
        smartPrintFloat(e, false, true, true);
    }
    printf("\n");

    return SUCCESS;
}

double evalPolyn (Polyn p, double x) {
    int e = INVALID_E;
    double result = 0;
    if (!p) return 0;
    for (p = p->next; p; p = p->next)
        if (e == INVALID_E) {
            e = p->element.e;
            result = p->element.p;
        } else {
            while (e-->p->element.e) result *= x;
            result += p->element.p;
        }
    while (e-->=0) result *= x;

    return result;
}

status diffPolyn (Polyn p, Polyn* result) {
    if (!p || !*result) return ERROR;
    Node *cur = *result, *next;

    for (p = p->next; p; p = p->next) {
        if (p->element.e) {
            initNode(&next, p->element.e * p->element.p, p->element.e-1);
            insertAfter(cur, next);
        }
        cur = next;
    }

    normalizePolyn(*result);
    return SUCCESS;
}

status intPolyn (Polyn p, Polyn* result) {
    if (!p || !*result) return ERROR;
    Node *cur = *result, *next;

    for (p = p -> next; p; p = p->next) {
        initNode(&next, p->element.p / (p->element.e + 1), p->element.e + 1);
        insertAfter(cur, next);
        cur = next;
    }

    normalizePolyn(*result);
    return SUCCESS;
}

status mulPolyn (Polyn pa, Polyn pb, Polyn* result) {
    if (!pa || !pb || !result) return ERROR;
    float p; int e;

    Node* cura, *curb, *cur, *tmp;

    for (curb = pb->next; curb; curb = curb->next) {
        cur = *result;
        for (cura = pa->next; cura; cura = cura->next) {
            p = cura->element.p * curb->element.p;
            e = cura->element.e + curb->element.e;
            while (!isTail(cur) && (isHead(cur) || cur->element.e > e)) cur = cur->next;
            if (!isHead(cur) && cur->element.e == e) {
                cur->element.p += p;
            } else {
                initNode(&tmp, p, e);
                insertAfter(cur, tmp);
                cur = tmp;
            }
        }
    }

    normalizePolyn(*result);
    return SUCCESS;
}

void selfMulPolyn (Polyn pol, float p, int e) {
    Node *n;

    for (n = pol->next; n; n = n->next) {
        n->element.e += e;
        n->element.p *= p;
    }
    normalizePolyn(pol);
}

status divmodPolyn (Polyn pa, Polyn pb, Polyn* divResult, Polyn* modResult) {
    if (isZeroPolyn(pb)) return ERROR;

    Polyn tmp, tmp2;
    Node* cur, *n;
    float p; int e;
    clonePolyn(pa, modResult);
    initPolyn(divResult);
    cur = *divResult;

    while (cmpPolyn(*modResult, pb) >= 0) {
        p = (*modResult)->next->element.p / pb->next->element.p;
        e = (*modResult)->next->element.e - pb->next->element.e;
        initNode(&n, p, e);
        insertAfter(cur, n);
        cur = n;

        clonePolyn(pb, &tmp);
        selfMulPolyn(tmp, p, e);
        initPolyn(&tmp2);
        substractPolyn(*modResult, tmp, &tmp2);
        destroyPolyn(modResult);
        *modResult = tmp2;
        destroyPolyn(&tmp);
    }

    normalizePolyn(*divResult);

    return SUCCESS;
}

// Main

#define ITEMS_N 10

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

void opAdd () {
    Polyn result;
    initPolyn(&result);
    if (addPolyn(pa, pb, &result)) {
        printf("Result: ");
        printPolyn(result);
    } else {
        printf("ERROR!\n");
    }
    destroyPolyn(&result);
}

void opSubstract () {
    Polyn result;
    initPolyn(&result);
    if (substractPolyn(pa, pb, &result)) {
        printf("Result: ");
        printPolyn(result);
    } else {
        printf("ERROR!\n");
    }
    destroyPolyn(&result);
}

void opPrint () {
    printf("Polyn A: ");
    printPolyn(pa);
    printf("Polyn B: ");
    printPolyn(pb);
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
    if (mulPolyn(pa, pb, &result)) {
        printf("Result: ");
        printPolyn(result);
    } else printf("ERROR!\n");

    destroyPolyn(&result);
}

void opDiv () {
    Polyn div = NULL, mod = NULL;

    if (divmodPolyn(pa, pb, &div, &mod)) {
        printf("Div part: ");
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

Operation operations[ITEMS_N] = {
    opCreate, opAdd, opSubstract, opPrint, opEval, opDiff, opInt, opMul, opDiv, opExit
};

int main () {
    while (1) {
        operations[choice(mainMenu, ITEMS_N-1)]();
        printf("\n");
    }
    return 0;
}
