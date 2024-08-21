#include "solve_quadr.h"

static void AnswerNorm(double *x1, double *x2);

enum NUM_ROOTS SolveQuadr(const struct Coeff *quadr_coeff, double *x1, double *x2) {

    double a = quadr_coeff->a, b = quadr_coeff->b, c = quadr_coeff->c;

    assert(IsFinite(a));
    assert(IsFinite(b));
    assert(IsFinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (IsNull(a)) {
        *x2 = NAN;
        return LinearEquation(quadr_coeff, x1);
    }

    double d = b * b - 4 * a * c;

    if (IsNull(d)) {
        *x1 = -b / (2 * a);
        *x2 = NAN;
        AnswerNorm(x1, x2);

        return ONE_ROOT;
    }

    if (d > 0) {

        if (IsNull(c)) {

            if (IsNull(b)) {
                *x1 = 0;
                *x2 = NAN;
                AnswerNorm(x1, x2);
                return ONE_ROOT;
            }

            if (-b / a < 0) {
                *x1 = -b / a;
                *x2 = 0;
                AnswerNorm(x1, x2);
            }
            else {
                *x1 = 0;
                *x2 = -b / a;
                AnswerNorm(x1, x2);
            }

            return TWO_ROOTS;
        }

        double sqrt_d = sqrt(d);

        if (a > 0) {
            *x1 = (-b - sqrt_d) / (2 * a);
            *x2 = (-b + sqrt_d) / (2 * a);
            AnswerNorm(x1, x2);
        }
        else {
            *x1 = (-b + sqrt_d) / (2 * a);
            *x2 = (-b - sqrt_d) / (2 * a);
            AnswerNorm(x1, x2);
        }

        return TWO_ROOTS;
    }

    return NO_ROOTS;
}

enum NUM_ROOTS LinearEquation(const struct Coeff *quadr_coeff, double *x) {

    assert(quadr_coeff != NULL);
    assert(IsNull(quadr_coeff->a));
    assert(x != NULL);

    double b = quadr_coeff->b, c = quadr_coeff->c;

    if (IsNull(b)) {

        if (IsNull(c)) {
            *x = INFINITY;
            return INF_ROOTS;
        }

        *x = NAN;
        return NO_ROOTS;
    }

    if (IsNull(c)) {
        *x = 0;
    }
    else {
        *x = -c / b;
    }
    return ONE_ROOT;
}

static void AnswerNorm(double *x1, double *x2) {
    if (IsNull(*x1)) {
        *x1 = 0;
    }
    if (IsNull(*x2)) {
        *x2 = 0;
    }
}
