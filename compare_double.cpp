#include "compare_double.h"

#include <string.h>
#include <math.h>

int IsInf(const double a) {
    static const double inf1 = INFINITY, inf2 = -INFINITY;
    return (memcmp(&a, &inf1, sizeof(a)) == 0 ||
            memcmp(&a, &inf2, sizeof(a)) == 0);
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
    if (IsNan(a) && IsNan(b)) {
    return 1;
    }
    if (IsInf(a) && IsInf(b)) {
    return 1;
    }
    return IsNull(a - b);
}

