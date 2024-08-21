#include <stdio.h>
#include <stdlib.h>

#include "indetify.h"
#include "bufer_clean.h"
#include "get_data.h"
#include "solve_quadr.h"
#include "show_results.h"

int main() {

    printf("quadratic equation solver \n");

    struct coeff quadr = {};
    int status = 0;

    status = GetData(&quadr);
    if (status == INPUT_ERROR) {
        printf("INPUT ERROR");
        return -1;
    }

    double x1 = 0, x2 = 0;

    int nRoots = SolveQuadr(&quadr, &x1, &x2);

    ShowResults(nRoots, x1, x2);
}
