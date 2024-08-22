#include <stdio.h>
#include <stdlib.h>

#include "define_consts.h"
#include "buffer_clean.h"
#include "get_data.h"
#include "solve_quadr.h"
#include "show_results.h"
#include "test_solve_quadr.h"

int main() {

    printf("quadratic equation solver \n");

    coefficients_t quadr = {};

    int statys = RunAllTests();
    (void) statys;

    int status = GetData(&quadr);
    if (status == INPUT_ERROR) {
        printf("INPUT ERROR");
        return EXIT_FAILURE;
    }

    double x1 = 0, x2 = 0;

    enum NUM_ROOTS nroots = QuadraticEquation(quadr.a, quadr.b, quadr.c, &x1, &x2);

    ShowResults(nroots, x1, x2);

    return EXIT_SUCCESS;
}
