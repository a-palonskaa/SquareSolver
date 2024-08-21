/**
 * @file test_solve_quadr.h
 * @brief Tests the function SolveQuadr that solve quadratic equations
 */
#ifndef TEST_SOLVE_QUADR_H
#define TEST_SOLVE_QUADR_H

#include <stdio.h>
#include <math.h>

#include "define_consts.h"
#include "solve_quadr.h"
/** @struct testing_data
  * @brief Structure for coefficients of quadraric equation
  * @var testing_data::coefficients
  * Member 'coefficients' is structure type of Coeff with the coeffcients of quadratic equation
  * @var testing_data::x1
  * Member 'x1' is the smallest root
  * @var testing_data::x2
  * Member 'x2' is the largest root
  * @var testing_data::nRoots
  * Member 'nRoots' is the number of roots type of NUM_ROOTS
  */
struct testing_data {
    struct Coeff coefficients;
    double x1;
    double x2;
    enum NUM_ROOTS nRoots;
};
/**
* @brief Run all tests of SolveQuadr function
* @return true if all tests were successful
*         false if there were mistakes
*/
bool RunAllTests();
/**
* @brief Run one test and print if there were mistakes and what mistake was detected
* @param[in] testnumber The number of test
* @param[in] quadr_coeff Pointer to the structure with equation coefficients
* @param[in] x1_expected Expected value of the smallest root
* @param[in] x2_expected Expected value of the greates root
* @param[in] nRoots_expected Expected value of the number of roots
* @return true if all tests were successful
*         false if there were mistakes
*/
bool RunTest(int testnumber, struct Coeff *quadr_coeff, double x1_expected, double x2_expected, enum NUM_ROOTS nRoots_expected);

#endif /* TEST_SOLVE_QUADR_H */
