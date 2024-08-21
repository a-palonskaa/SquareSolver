#include "test_solve_quadr.h"

bool RunTest(int testnumber, struct Coeff *quadr_coeff, double x1_expected, double x2_expected, enum NUM_ROOTS nRoots_expected) {

    double x1 = 0, x2 = 0;
    enum NUM_ROOTS nRoots = SolveQuadr(quadr_coeff, &x1, &x2);
// сначала вывести об ошибке кол-ва корней если есть

    if (!(nRoots == nRoots_expected)) {
        printf("Error number of root nRoots = %d, expected nRoots = %d \n", nRoots, nRoots_expected);
        return 1;
    }
    else if (!(IsEqual(x1, x1_expected) && IsEqual(x2, x2_expected))) {
        printf("Error Test No%d, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg\n"
               "Expected x1 = %lg, x2 = %lg.\n",
               testnumber, quadr_coeff->a, quadr_coeff->b, quadr_coeff->c, x1, x2,
               x1_expected, x2_expected);
        return 1;
    }

    printf("Successful test No%d  \n", testnumber);
    return 0;
}

bool RunAllTests() {
    size_t i = 0;
    struct testing_data tests[]={
                                 {{ 0,  0,  0}, INFINITY, NAN, INF_ROOTS},
                                 {{ 1,  0,  0},        0, NAN,  ONE_ROOT},
                                 {{ 0,  0,  1},      NAN, NAN,  NO_ROOTS},
                                 {{ 0,  1,  0},        0, NAN,  ONE_ROOT},
                                 {{ 1,  2,  1},       -1, NAN,  ONE_ROOT},
                                 {{ 1,  2,  0},       -2,   0, TWO_ROOTS},
                                 {{-1,  2,  0},        0,   2, TWO_ROOTS},
                                 {{ 1,  2, -3},       -3,   1, TWO_ROOTS},
                                 {{ 1, -5,  4},        1,   4, TWO_ROOTS},
                                 {{ 0,  5,  1},     -0.2, NAN,  ONE_ROOT},
                                 {{ 1,  0, -4},       -2,   2, TWO_ROOTS}

   };
    size_t length = sizeof(tests) / sizeof(tests[0]);
    while (i < length) {
        if (RunTest(i+1, &(tests[i].coefficients), tests[i].x1, tests[i].x2, tests[i].nRoots)) return 0;
        i++;
    }

    return 1;
}
