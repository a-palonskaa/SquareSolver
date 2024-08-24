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
 * @param[in] a Coefficient at the 2nd degree
 * @param[in] b Coefficient at the 1st degree
 * @param[in] c Free member coefficient
 * @param[out] x1 The smallest root(or INFINITY/ NAN)
 * @param[out] x2 The greatest root(or INFINITY/ NAN)
 * @return number of roots type of NUM_ROOTS
 */
enum NUM_ROOTS QuadraticEquation(double a, double b, double c, double *x1, double *x2);

/**
 * @brief Solve a linear equation, write the root of linear equation, and return number of roots
 * @param[in] b Coefficient at the 1st degree
 * @param[in] c Free member coefficient
 * @param[out] x Root of the equation(NAN if there are no roots)
 * @return number of roots type of NUM_ROOTS
 */
enum NUM_ROOTS LinearEquation(double b, double c, double *x);

#endif /* SOLVE_QUADR_H */
