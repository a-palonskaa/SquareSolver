/**
 * @file solve_quadr.h
 * @brief Solve the quadratic equation knowing the coefficients
 */
#ifndef SOLVE_QUADR_H
#define SOLVE_QUADR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "get_data.h"
#include "compare_double.h"
/**
* @brief Solve the quadratic equation, write the roots, and return number of roots
* @param[in] quadr_coeff Pointer to the structure with coefficients
* @param[out] x1 The smallest root(or INFINITY/ NAN)
* @param[out] x2 The greatest root(or INFINITY/ NAN)
* @return number of roots type of NUM_ROOTS
*/
enum NUM_ROOTS SolveQuadr(const struct Coeff *quadr_coeff, double *x1, double *x2);
/**
* @brief Solve a linear equation, write the root of linear equation, and return number of roots
* @param[in] quadr_coeff Pointer to the structure with coefficients
* @param[out] x Root of the equation(NAN if there are no roots)
* @return number of roots type of NUM_ROOTS
*/
enum NUM_ROOTS LinearEquation(const struct Coeff *quadr_coeff, double *x);

#endif /* SOLVE_QUADR_H */
