#include "show_results.h"

int ShowResults(enum NUM_ROOTS nroots, const double x1, const double x2, FILE *file) {

    switch (nroots) {
        case NO_ROOTS:
            fprintf(file, "No roots! \n");
            break;
        case ONE_ROOT:
            fprintf(file, "x1 = %.2lf \n", x1);
            break;
        case TWO_ROOTS:
            fprintf(file, "x1 = %.2lf, x2 = %.2lf \n", x1, x2);
            break;
        case INF_ROOTS:
            fprintf(file, "Any number \n");
            break;
        case NON_VALID_INPUT:
            fprintf(file, "Non-valid input  \n");
            break;
        default:
            assert(0 && "ERROR nroots");
            fclose(file);
            return 1;
    }
    fclose(file);
    return 0;
}
