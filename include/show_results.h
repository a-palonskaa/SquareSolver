/**
 * @file show_results.h
 * @brief Print the results of solving quadratic equation
 */
#ifndef SHOW_RESULTS_H
#define SHOW_RESULTS_H

#include <stdio.h>
#include <assert.h>

#include "define_consts.h"
/**
* @brief Print the values of ​​the roots or an error message
* @param[in] n_roots Number of roots type of NumRoots
* @param[in] x1 The smallest root(or INFINITY/ NAN)
* @param[in] x2 The greatest root(or INFINITY/ NAN)
* @return 1 if the error emerged
          0 if successfully printed the solution
*/
int ShowResults(enum NumRoots n_roots, const double x1, const double x2, FILE *file);

#endif /* SHOW_RESULTS_H */
