#include "show_results.h"

int ShowResults(enum NumRoots n_roots, const double x1, const double x2, FILE *file) {
    assert(file != nullptr);

    switch (n_roots) {
        case NO_ROOTS:
            fprintf(file, "No roots!" "\n");
            break;
        case ONE_ROOT:
            fprintf(file, "x1 = %.8lf" "\n", x1);
            break;
        case TWO_ROOTS:
            fprintf(file, "x1 = %.8lf, x2 = %.2lf" "\n", x1, x2);
            break;
        case INF_ROOTS:
            fprintf(file, "Any number" "\n");
            break;
        case NON_VALID_INPUT:
            fprintf(file, "Non-valid input" "\n");
            break;
        default:
            assert(0 && "ERROR n_roots");
            return 1;
    }
    return 0;
}
