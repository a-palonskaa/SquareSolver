#include "solve_quadr.h"

enum NUM_ROOTS SolveQuadr(const struct Coeff *quadr_coeff, double *x1, double *x2) {

    double a = quadr_coeff->a, b = quadr_coeff->b, c = quadr_coeff->c;

    assert(IsFinite(a));
    assert(IsFinite(b));
    assert(IsFinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (!IsNull(a)) {

        double d = b * b - 4 * a * c;

        if (IsNull(d)) {

            *x1 = -b / (2 * a);
            *x2 = NAN;

            return ONE_ROOT;
        }
        if (d > 0) {

            if (IsNull(c)) {

                if (IsNull(b)) {
                    *x1 = 0;
                    *x2 = NAN;
                    return ONE_ROOT;
                }

                if (-b / a < 0) {
                    *x1 = -b / a;
                    *x2 = 0;
                }
                else {
                    *x1 = 0;
                    *x2 = -b / a;
                }

                return TWO_ROOTS;
            }

            double sqrt_d = sqrt(d);

            if (a > 0) {
                *x1 = (-b - sqrt_d) / (2 * a);
                *x2 = (-b + sqrt_d) / (2 * a);
            }
            else {
                *x1 = (-b + sqrt_d) / (2 * a);
                *x2 = (-b - sqrt_d) / (2 * a);
            }

            return TWO_ROOTS;
        }
        return NO_ROOTS;
    }

    if (!IsNull(b)) {

        *x1 = -c / b;
        *x2 = NAN;

        return ONE_ROOT;
    }

    if (IsNull(c)) {

        *x1 = -INFINITY;
        *x2 = INFINITY;

        return INF_ROOTS;
    }

    *x1 = NAN;
    *x2 = NAN;

    return NO_ROOTS;
}


// TODO: проверка сортировка корней, частные случаи, проверка Nan,
// TODO: gjvtyznm vtcnfbv kjubre (cyfxfkf kbytqyjt)

//make файлы
