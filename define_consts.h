#ifndef DEFINE_CONSTS_H
#define DEFINE_CONSTS_H

#include <stdio.h>


enum ERRORS {
    INPUT_ERROR        = 0,
    ROOTS_NUMBER_ERROR = 1,
    END_OF_FILE = 0,
    SYMBOLS_INPUT_ERROR = 1,
    NO_ERRORS = 2
 };

enum NUM_ROOTS {
    NO_ROOTS  = 0,
    ONE_ROOT  = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1
};

struct Coeff {
    double a;
    double b;
    double c;
};

#endif /* DEFINE_CONSTS_H */
