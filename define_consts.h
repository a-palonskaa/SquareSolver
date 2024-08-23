/**
 * @file define_consts.h
 * @brief Functions to define types and structures.
 */
#ifndef DEFINE_CONSTS_H
#define DEFINE_CONSTS_H

#include <stdio.h>
/**
 * @brief enum for errors type
 */

const int MAXLINE = 500;

enum ERRORS {
    NO_INPUT_ERRORS     = -1,   ///< no input errors
    INPUT_ERROR         =  0,   ///< input error
    ROOTS_NUMBER_ERROR  =  1,   ///< error number of roots
    END_OF_FILE         =  0,   ///< end of file
    SYMBOLS_INPUT_ERROR =  1,   ///< error of detecting non-number, non-spaces symbols
    NO_ERRORS           =  2    ///< no errors
};
/**
 * @brief enum for number of roots definition
 */
enum NUM_ROOTS {
    INF_ROOTS =      -1,   ///< infinite number of roots
    NO_ROOTS  =       0,   ///< no roots
    ONE_ROOT  =       1,   ///< one root
    TWO_ROOTS =       2,   ///< two roots
    NON_VALID_INPUT = 3    ///< non valid input
};
/** @struct coefficients_t
  * @brief Structure for coefficients of quadraric equation
  * @var Coeff::a
  * Member 'a' is a coefficient at the 2nd degree
  * @var Coeff::b
  * Member 'b' is a coefficient at the 1st degree
  * @var Coeff::c
  * Member 'c' is a free member coefficient
  */
typedef struct {
    double a;
    double b;
    double c;
} coefficients_t;

#endif /* DEFINE_CONSTS_H */
