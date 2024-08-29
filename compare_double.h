/**
 * @file compare_double.h
 * @brief Functions to compare variables of type double with:
 *        NULL, NAN, INFINITY, and other double variable
 */
#ifndef COMPARE_DOUBLE
#define COMPARE_DOUBLE

#include <stdio.h>

/**
 * @brief Check if variable is not NAN or INFINITY
 * @param[in] a Variable to check
 * @return 1 if variable is not NAN or INFINITY, 0 in other case
 */
int IsFinite(const double a);

/**
 * @brief Check if variable is NAN
 * @param[in] a Variable to check
 * @return 1 if variable is NAN, 0 in other case
 */
int IsNan(const double a);

/**
 * @brief Check if variable is INFINITY
 * @param[in] a Variable to check
 * @return 1 if variable is INFINITY, 0 in other case
 */
int IsInf(const double a);

/**
 * @brief Check if variable is NULL
 * @param[in] a Variable to check
 * @return 1 if variable is NULL, 0 in other case
 */

int IsNull(const double a);
/**
 * @brief Check if variables type of double are equal
 * @param[in] a Variable to compare
 * @param[in] b varible to compare
 * @return 1 if variable are equal, 0 in other case
 * @details Doubles are compared taking into account the error,
 *          which depends on the values ​​of the variables being compared.
 *          NAN and NAN, INF and INF, -INF and -INF are considered to be equal.
 */
int IsEqual(const double a, const double b);

/**
 * @brief Find max double out of two
 * @param[in] a Variable to compare
 * @param[in] b varible to compare
 * @return max out of two values
 */
double MaxTwo(const double a, const double b);

/**
 * @brief Find max double out of three
 * @param[in] a Variable to compare
 * @param[in] b varible to compare
 * @return max out of three value
 */
double MaxThree(const double a, const double b, const double c);

#endif /* COMPARE_DOUBLE_H */
