/**
 * @file define_consts.h
 * @brief Functions to define types and structures.
 */
#ifndef DEFINE_CONSTS_H
#define DEFINE_CONSTS_H

#include <stdio.h>

const int MAXLINE = 500;

/**
 * @brief enum for flags
 */
enum class VALIDATION {
    DEFAULT = 0,
    ACTIVE  = 1
};

enum FLAGS {
    SOLVE = 0,
    TEST  = 1
};

enum class OUTPUT_FLAGS {
    CONSOLE = 0,
    FILE    = 1
};

enum class INPUT_FLAGS {
    CONSOLE = 0,
    FILE    = 1
};

/**
 * @brief enum for errors type
 */
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
    INF_ROOTS       = -1,   ///< infinite number of roots
    NO_ROOTS        =  0,   ///< no roots
    ONE_ROOT        =  1,   ///< one root
    TWO_ROOTS       =  2,   ///< two roots
    NON_VALID_INPUT =  3    ///< non valid input
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

typedef struct {
    enum FLAGS         mode;                 ///< default status solve mode
    enum VALIDATION    mode_test_valid;
    enum VALIDATION    mode_solve_valid;
    enum OUTPUT_FLAGS  output;               ///< default status print to console
    enum VALIDATION    output_console_valid;
    enum VALIDATION    output_file_valid;
    enum INPUT_FLAGS   input;
    enum VALIDATION    input_console_valid;  ///< default status read from console
    enum VALIDATION    input_file_valid;
    const char*        file_input;           ///< pointer to the string with input file name
    const char*        file_output;          ///< pointer to the string with output file name
} flags_t;

enum LOG_LEVEL {
    DEBUG   = 0,
    INFO    = 1,
    WARNING = 2,
    ERROR   = 3
};


#endif /* DEFINE_CONSTS_H */

