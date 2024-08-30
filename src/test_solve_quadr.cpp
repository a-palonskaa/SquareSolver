#include "test_solve_quadr.h"

/**
* @brief Print results of the testing
* @param[out] test Pointer to the structure type of testing_t
* @param[out] storage Pointer to the untyped variable
*/
static void PrintTestsReport(testing_t* test, void *storage);

/**
* @brief Rewrite roots in ascending order
* @param[out] test Pointer to the structure type of testing_t
* @param[out] storage Pointer to the untyped variable
*/
static void TestExecute(testing_t *test, void *storage);

void PrintTestsReport(testing_t* test, void *storage) {
    assert(test != nullptr);
    assert(storage != nullptr);

    store_data_t* data = (store_data_t*)(storage);
    coefficients_t* coeff = &data->testing_data.coefficients;
    roots_t* roots = &data->roots_returned;

    if (test->status == STATE::DEFAULT) {
        Log(INFO, "Test No. %d successful \n", test->test_number + 1);
    }
    else if (!(roots->nroots == data->testing_data.roots_expected.nroots)){
        Log(ERROR, "Error Test No%d a = %lg, b = %lg, c = %lg \n"
                   "number of root nroots = %d, expected nroots = %d \n",
                   test->test_number + 1,
                   coeff->a, coeff->b, coeff->c,
                   roots->nroots, data->testing_data.roots_expected.nroots);
    }
    else {
        Log(ERROR, "Error Test No%d, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg\n"
                    "Expected x1 = %lg, x2 = %lg.\n",
                    test->test_number + 1, coeff->a, coeff->b, coeff->c, roots->x1, roots->x2,
                    data->testing_data.roots_expected.x1, data->testing_data.roots_expected.x2);
    }
}

void TestExecute(testing_t *test, void* storage) {
    assert(test != nullptr);
    assert(storage != nullptr);

    store_data_t* data = (store_data_t*)(storage);
    coefficients_t* coeff = &data->testing_data.coefficients;
    roots_t* roots = &data->roots_returned;

    roots->nroots = QuadraticEquation(coeff->a, coeff->b, coeff->c, &roots->x1, &roots->x2);

    ASSERT_EQUAL(test, data->testing_data.roots_expected.nroots, roots->nroots);
    ASSERT_EQUAL_DOUBLE(test, data->testing_data.roots_expected.x1, roots->x1);
    ASSERT_EQUAL_DOUBLE(test, data->testing_data.roots_expected.x2, roots->x2);
}

bool RunAllTests() {
    int status = 0;

    const testing_data_t tests[]={          // a,  b,  c,         x1,  x2,          nRoots
                                 {{            0,  0,  0},{ INFINITY, NAN,       INF_ROOTS}},
                                 {{            1,  0,  0},{        0, NAN,        ONE_ROOT}},
                                 {{            0,  0,  1},{      NAN, NAN,        NO_ROOTS}},
                                 {{            0,  1,  0},{        0, NAN,        ONE_ROOT}},
                                 {{            1,  2,  1},{       -1, NAN,        ONE_ROOT}},
                                 {{            1,  2,  0},{       -2,   0,       TWO_ROOTS}},
                                 {{           -1,  2,  0},{        0,   2,       TWO_ROOTS}},
                                 {{            1,  2, -3},{       -3,   1,       TWO_ROOTS}},
                                 {{            1, -5,  4},{        1,   4,       TWO_ROOTS}},
                                 {{            0,  5,  1},{     -0.2, NAN,        ONE_ROOT}},
                                 {{            1,  0, -4},{       -2,   2,       TWO_ROOTS}},
                                 {{         1e-9,  0,  0},{ INFINITY, NAN,       INF_ROOTS}},
                                 {{          NAN,  0,  0},{      NAN, NAN, NON_VALID_INPUT}}
   };

    const size_t length = sizeof(tests) / sizeof(tests[0]);

    testing_t tresults = {};

    store_data_t storage = {};
    tresults.test_execute = &TestExecute;
    tresults.print_message = &PrintTestsReport;

    for (size_t i = 0; i < length; i++) {
        storage.testing_data = tests[i];
        status += TestRun(&tresults, (int) i, &storage);
    }

    return status != 0;
}
