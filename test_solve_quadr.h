#ifndef TEST_SOLVE_QUADR_H
#define TEST_SOLVE_QUADR_H

#include <stdio.h>
#include <math.h>

#include "define_consts.h"
#include "solve_quadr.h"

struct testing_data {
    struct Coeff coefficients;
    double x1;
    double x2;
    enum NUM_ROOTS nRoots;
};

bool RunAllTests();
bool RunTest(int testnumber, struct Coeff *quadr_coeff, double x1_expected, double x2_expected, enum NUM_ROOTS nRoots_expected);

#endif /* TEST_SOLVE_QUADR_H */
