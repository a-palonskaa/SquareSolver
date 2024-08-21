#include "test_solve_quadr.h"

bool RunTest(int testnumber, struct Coeff *quadr_coeff, double x1_expected, double x2_expected, enum NUM_ROOTS nRoots_expected) {
    double x1 = 0, x2 = 0;
    enum NUM_ROOTS nRoots = SolveQuadr(quadr_coeff, &x1, &x2);
    if (!IsEqual(nRoots, nRoots_expected) || !IsEqual(x1, x1_expected) || !IsEqual(x2, x2_expected)) {
        printf("Error Test No%d, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d. \n"
               " Expected x1 = %lg, x2 = %lg, nRoots = %d \n",
               testnumber, quadr_coeff->a, quadr_coeff->b, quadr_coeff->c, x1, x2, nRoots,
               x1_expected, x2_expected, nRoots_expected);
        return 1;
    }
    printf("Successful test No%d  \n", testnumber);
    return 0;
}

bool RunAllTests() {
    struct Coeff testing_coeff = {};
    if (RunTest(1, &testing_coeff, -INFINITY, INFINITY, INF_ROOTS)) return 0;
    testing_coeff = Coeff{1, 0, 0};
    if (RunTest(2, &testing_coeff, 0, NAN, ONE_ROOT)) return 0;
    testing_coeff = Coeff{0.0, 0.0, 0.1};
    if (RunTest(3, &testing_coeff, NAN, NAN, NO_ROOTS)) return 0;
    /* if (RunTest(4, {0, 1, 0}, 0, NAN, ONE_ROOT)) return 0;
    if (RunTest(5, {1, 2, 1}, -1, NAN, ONE_ROOT)) return 0;
    if (RunTest(6, {1, 2, 0}, -2, 0, TWO_ROOTS)) return 0;
    if (RunTest(7, {-1, 2, 0}, 0, 2, TWO_ROOTS)) return 0;
    if (RunTest(8, {1, 2, -3}, -3, 1, TWO_ROOTS)) return 0;
    if (RunTest(9, {1, -5, 4}, 1, 4, TWO_ROOTS)) return 0;
    if (RunTest(10, {0, 5, 1}, -0.2, NAN, ONE_ROOT)) return 0;
    if (RunTest(11, {1, 0, -4}, -2, 2, TWO_ROOTS)) return 0; */
    return 1;
}
