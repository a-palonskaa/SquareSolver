#include "compare_double.h"

#include <string.h>
#include <math.h>

int IsInf(const double a) {
    static const double inf1 = INFINITY, inf2 = -INFINITY;
    return ((memcmp(&a, &inf1, sizeof(a)) == 0) -
            (memcmp(&a, &inf2, sizeof(a)) == 0));
}

int IsNan(const double a) {
    return (a != a);
}

int IsFinite(const double a) {
    return !(IsNan(a) || IsInf(a));
}

int IsNull(const double num) {
    return IsEqual(num, 0);
}

int IsEqual(const double a, const double b) {
    static const double epsilon = 0.00000001;

    if (IsNan(a) && IsNan(b)) {
        return 1;
    }

    if ((IsInf(a) > 0 && IsInf(b) > 0) ||
        (IsInf(a) < 0 && IsInf(b) < 0)) {
        return 1;
    }

    if (IsFinite(a) && IsFinite(b)) {
        return fabs(a - b) <= epsilon * MaxThree(1, fabs(a), fabs(b));
    }

    return 0;
}

double MaxTwo(double a, double b) {
    return (a > b) ? a : b;
}

double MaxThree(double a, double b, double c) {
    return MaxTwo(c, MaxTwo(a, b));
}
