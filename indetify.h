#ifndef INDETIFY_H
#define INDETIFY_H

#include <stdio.h>

 // const int INPUT_ERROR = 0

enum mistakes {
    INPUT_ERROR        = 0;
    ROOTS_NUMBER_ERROR = 1;
 };

enum NUM_ROOTS {
    NO_ROOTS  = 0,
    ONE_ROOT  = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1
};

struct coeff {
    double a;
    double b;
    double c;
};

#endif /* INDETIFY_H */
