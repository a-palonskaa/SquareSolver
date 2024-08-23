/**
 * @file test_library.h
 * @brief Library for testing data
 */
#ifndef TEST_LIBRARY_H
#define TEST_LIBRARY_H

#include <stdio.h>

#include "define_consts.h"
#include "compare_double.h"

//=======================================================================================

#define ASSERT_TRUE(test, expr)             \
    do {                                    \
        if (!expr) {                        \
            test->status = STATE::ERROR;    \
            return;                         \
        }                                   \
    } while (0)

#define ASSERT_FALSE(test, stat)            \
    do {                                    \
        if (expr) {                         \
            test->status = STATE::ERROR;    \
            return;                         \
        }                                   \
    } while (0)

#define ASSERT_EQUAL(test, state, want)    \
    do {                                    \
            if (state != want) {            \
            test->status = STATE::ERROR;    \
            return;                         \
        }                                   \
    } while (0);

#define ASSERT_EQUAL_DOUBLE(test, a, b)     \
    do {                                    \
            if (!IsEqual(a, b)) {            \
            test->status = STATE::ERROR;    \
            return;                         \
        }                                   \
    } while (0);

//=======================================================================================

#define CHECK_TRUE(test, expr)              \
    do {                                    \
        if (!expr) {                        \
            test->status = STATE::ERROR;    \
        }                                   \
    } while (0)

#define CHECK_FALSE(test, stat)             \
    do {                                    \
        if (expr) {                         \
            test->status = STATE::ERROR;    \
        }                                   \
    } while (0)

#define CHECK_EQUAL(test, state, want)      \
    do {                                    \
            if(state != want) {             \
            test->status = STATE::ERROR;    \
        }                                   \
    } while (0);

#define CHECK_EQUAL_DOUBLE(test, a, b)      \
    do {                                    \
            if(!IsEqual(a, b)) {            \
            test->status = STATE::ERROR;    \
        }                                   \
    } while (0);

//=======================================================================================

typedef void (*printer_t)(struct Testing *test, void *storage);
typedef void (*test_t)(struct Testing *test, void *storage);
/**
 * @brief enum for define the STATE while checking for errors
 */
enum class STATE {
    DEFAULT = true,  ///< no errors(default state)
    ERROR  = false  ///< error
};
enum LOG_LEVEL {
    ERROR   = 0,
    WARNING = 1,
    INFO    = 2,
    DEBUG   = 3
};
/** @struct testing_t
 * @brief Structure for the testing information
 * @var testing_t::status
 * Member 'status' is a status of the testing(default or error)
 * @var testing_t::test_number
 * Member 'test_number' is a number of the test
 * @var testing_t::output
 * Member 'output' is a pointer to the opened file for output or NULL in case of failed opening
 * @var testing_t::run
 * Member 'run' is a pointer to the function that returns bool and takes pointer to the non-defined-type and poiner to the structure type of Testing
 * @var testing_t::print_message
 * Member 'print_message' is a pointer to the function that does not return anything and takes pointer to the non-defined-type and poiner to the structure type of Testing
 */
typedef struct Testing {
    enum STATE status;
    int test_number;
    FILE *output;
    test_t  run;
    printer_t print_message;
    enum LOG_LEVEL min_level;
} testing_t;
/**
* @brief Run the test of quadratic equation
* @param[in] test Pointer to the testing_t structure
* @param[in] test_number Number of the test
* @param[in] data Pointer to the non-defined-type variable
*/
void TestRun(testing_t *test, int test_number, void *data);

#endif /* TEST_LIBRARY_H */
