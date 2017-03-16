#ifndef POLYN_H_
#define POLYN_H_

#include "linkedlist.h"
#include "status.h"

typedef Node *Polyn;

bool isZeroPolyn (Polyn p);

int cmpPolyn (Polyn pa, Polyn pb);

status initPolyn (Polyn* list);

status destroyPolyn (Polyn* list);

void createPolyn (Polyn* p, int m);

status addPolyn (Polyn pa, Polyn pb, Polyn* result);

status substractPolyn (Polyn pa, Polyn pb, Polyn* result);

status printPolyn (Polyn p);

double evalPolyn (Polyn p, double x);

status diffPolyn (Polyn p, Polyn* result);

status intPolyn (Polyn p, Polyn* result);

status mulPolyn (Polyn pa, Polyn pb, Polyn* result);

status divmodPolyn (Polyn pa, Polyn pb, Polyn* divResult, Polyn* modResult);

#endif
