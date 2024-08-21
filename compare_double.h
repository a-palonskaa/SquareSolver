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
 */

int IsEqual(const double a, const double b);

#endif /* COMPARE_DOUBLE_H */
