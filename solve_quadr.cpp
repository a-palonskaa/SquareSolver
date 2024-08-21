#include "solve_quadr.h"


int SolveQuadr(const struct coeff *pointer, const double *px1, const double *px2) {

    double a = pointer->a, b = pointer->b, c = pointer->c;

    assert(is_finite(a));
    assert(is_finite(b));
    assert(is_finite(c));

    assert(px1 != NULL);
    assert(px2 != NULL);
    assert(px1 != px2);

    if (!IsNull(a)) {

        double d = b * b - 4 * a * c;

        if(IsNull(d)) {

            *px1 = -b / (2 * a);

            return ONE_ROOT;
        }
        if(d > 0) {

            double sqrt_d = sqrt(d);

            *px1 = (sqrt_d - b) / (2 * a);
            *px2 = -(sqrt_d + b)/(2 * a);

            return TWO_ROOTS;
        }
        return NO_ROOTS;
    }

    if(!IsNull(b)) {

        *px1 = -c / b;

        return ONE_ROOT;
    }

    if (IsNull(c)) {

        return INF_ROOTS;
    }

    return NO_ROOTS;
}
