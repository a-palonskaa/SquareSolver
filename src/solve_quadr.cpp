#include "solve_quadr.h"

/**
* @brief Rewrite roots in ascending order
* @param[out] x1 Pointer to the smaller root
* @param[out] x2 Pointer to the greater root
*/
static void AnswerNormalization(double *x1, double *x2);

enum NUM_ROOTS QuadraticEquation(double a, double b, double c, double *x1, double *x2) {
    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    if (IsFinite(a) == 0 ||
        IsFinite(b) == 0 ||
        IsFinite(c) == 0 ) {
        *x1 = NAN;
        *x2 = NAN;
        return NON_VALID_INPUT;
    }

    if (IsNull(a)) {
        *x2 = NAN;
        return LinearEquation(b, c, x1);
    }

    double d = b * b - 4 * a * c;

    if (IsNull(d)) {
        *x1 = -b / (2 * a);
        *x2 = NAN;
        AnswerNormalization(x1, x2);
        return ONE_ROOT;
    }

    if (d > 0) {

        if (IsNull(c)) {

            if (IsNull(b)) {
                *x1 = 0;
                *x2 = NAN;
                AnswerNormalization(x1, x2);
                return ONE_ROOT;
            }

            if (-b / a < 0) {
                *x1 = -b / a;
                *x2 = 0;
                AnswerNormalization(x1, x2);
            }
            else {
                *x1 = 0;
                *x2 = -b / a;
                AnswerNormalization(x1, x2);
            }
            return TWO_ROOTS;
        }

        double sqrt_d = sqrt(d);

        if (a > 0) {
            *x1 = (-b - sqrt_d) / (2 * a);
            *x2 = (-b + sqrt_d) / (2 * a);
            AnswerNormalization(x1, x2);
        }
        else {
            *x1 = (-b + sqrt_d) / (2 * a);
            *x2 = (-b - sqrt_d) / (2 * a);
            AnswerNormalization(x1, x2);
        }
        return TWO_ROOTS;
    }
    return NO_ROOTS;
}

enum NUM_ROOTS LinearEquation(double b, double c, double *x) {
    assert(x != nullptr);

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

static void AnswerNormalization(double *x1, double *x2) {
    if (IsNull(*x1)) {
        *x1 = 0;
    }
    if (IsNull(*x2)) {
        *x2 = 0;
    }
}
