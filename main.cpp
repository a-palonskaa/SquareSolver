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

    struct Coeff quadr = {};

    int statys = RunAllTests();
    (void) statys;

    int status = GetData(&quadr);
    if (status == INPUT_ERROR) {
        printf("INPUT ERROR");
        return -1;
    }

    double x1 = 0, x2 = 0;

    enum NUM_ROOTS nRoots = SolveQuadr(&quadr, &x1, &x2);

    ShowResults(nRoots, x1, x2);
}
