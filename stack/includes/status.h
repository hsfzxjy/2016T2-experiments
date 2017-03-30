#ifndef _STATUS_H_
#define _STATUS_H_

#include <stdlib.h>
#include <stdio.h>

typedef int status;

#define SUCCESS 1
#define ERROR 0
#define OVERFLOW -1
#define DIVIDED_BY_ZERO -2

#define raise(errcode) do { \
    printf("Error occured!\n"); \
    exit(errcode); \
} while (0);

#endif
