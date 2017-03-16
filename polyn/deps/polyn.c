#include <stdio.h>
#include <stdlib.h>

#include "ioutil.h"
#include "status.h"
#include "polyn.h"
#include "linkedlist.h"
#include "mathutil.h"

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
