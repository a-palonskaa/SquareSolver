#include "compare_double.h"

#include <string.h>
#include <math.h>

int IsInf(const double a) {
    return (a == INFINITY || a == -INFINITY);
}

int IsNan(const double a) {
    return (a != a);
}

int IsFinite(const double a) {
    return !(IsNan(a) || IsInf(a));
}


int IsNull(const double num) {
    static const double epsilon = 0.00000001;
    return (fabs(num) < epsilon);
}

int IsEqual(const double a, const double b) {
    return IsNull(a - b);
}

