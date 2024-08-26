/**
 * @file test_solve_quadr.h
 * @brief Test the function QuadraticEquation that solve quadratic equations
 */
#ifndef TEST_SOLVE_QUADR_H
#define TEST_SOLVE_QUADR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>


#include "define_consts.h"
#include "solve_quadr.h"
#include "test_library.h"
#include "compare_double.h"
#include "print_colors.h"
#include "logger.h"

/** @struct Roots_expected
 * @brief Structure for the expected roots
 *@var Roots_expected::x1
 * Member 'x1' is the smallest expected root
 * @var Roots_expected::x2
 * Member 'x2' is the greatest expected root
 * @var Roots_expected::x2
 * Member 'x2' is the greatest expected root
 */
typedef struct {
    double x1;
    double x2;
    enum NUM_ROOTS nroots;
} roots_t;

/** @testing_t_data
  * @brief Structure for testing data (coefficients of quadraric equation and expected roots)
  * @var testing_data::coefficients
  * Member 'coefficients' is structure type of coefficients_t with the coeffcients of quadratic equation
  * @var testing_data::roots_expected
  * Member 'roots_expected' is structure type of roots_t with the roots and their amount
  */
typedef struct {
    coefficients_t coefficients;
    roots_t roots_expected;
} testing_data_t;

/** @store_data_t
  * @brief Structure for the testing data and data obtained by the programs' algorithm
  * @var store_data_t::testing_data
  * Member 'coefficients' is structure type of testing_data_t with the testing data
  * @var store_data_t::roots_returned
  * Member 'roots_returned' is structure type of roots_t with the obtained roots and their amount by the quadratic equation solver
  */
typedef struct {
    testing_data_t testing_data;
    roots_t roots_returned;
} store_data_t;

/**
* @brief Run all tests of QuadraticEquation function
* @return true if all tests were successful
*         false if there were mistakes
*/
bool RunAllTests();

#endif /* TEST_SOLVE_QUADR_H */
