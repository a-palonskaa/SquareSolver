#ifndef SOLVE_QUADR_H
#define SOLVE_QUADR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "get_data.h"
#include "compare_double.h"

enum NUM_ROOTS SolveQuadr(const struct Coeff *quadr_coeff, double *x1, double *x2);

#endif /* SOLVE_QUADR_H */
