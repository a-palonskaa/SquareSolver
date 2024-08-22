#include "test_solve_quadr.h"

static void PrintMessage(testing_t* test, void *storage);
static bool Run(testing_t *test, void* storage);

void PrintMessage(testing_t* test, void *storage) {

    store_data_t* data = (store_data_t*)(storage);

        if (test->status == DEFAULT) {
            fprintf(test->output, "Test No. %d successful \n", test->test_number + 1);
        }
        else if (!(data->roots_returned.nroots == data->testing_data.roots_expected.nroots)){
            fprintf(test->output, "Error Test No%d a = %lg, b = %lg, c = %lg \n"
                                  "number of root nroots = %d, expected nroots = %d \n",
                                  test->test_number + 1,
                                  data->testing_data.coefficients.a, data->testing_data.coefficients.b, data->testing_data.coefficients.c,
                                  data->roots_returned.nroots, data->testing_data.roots_expected.nroots);
        }
        else {
            fprintf(test->output, "Error Test No%d, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg\n"
                                  "Expected x1 = %lg, x2 = %lg.\n",
                                  test->test_number + 1, data->testing_data.coefficients.a, data->testing_data.coefficients.b, data->testing_data.coefficients.c, data->roots_returned.x1, data->roots_returned.x2,
                                  data->testing_data.roots_expected.x1, data->testing_data.roots_expected.x2);
        }

}


bool Run(testing_t *test, void* storage) {

    store_data_t* data = (store_data_t*)(storage);

    data->roots_returned.nroots = QuadraticEquation(data->testing_data.coefficients.a, data->testing_data.coefficients.b, data->testing_data.coefficients.c, &(data->roots_returned.x1), &(data->roots_returned.x2));
    if (IsEqual(data->testing_data.roots_expected.x1, data->roots_returned.x1) &&
          IsEqual(data->testing_data.roots_expected.x2, data->roots_returned.x2) &&
          IsEqual(data->roots_returned.nroots, data->testing_data.roots_expected.nroots)) {
        test->status = DEFAULT;
        test->print_message(test, data);
        ASSERT_EQUAL(test->status);
    }
    test->status = ERROR;
    test->print_message(test, data);
    ASSERT_EQUAL(test->status);
}

bool RunAllTests() {

    testing_data_t tests[]={
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
                                 {{0.00000000001,  0,  0},{ INFINITY, NAN,       INF_ROOTS}},
                                 {{          NAN,  0,  0},{      NAN, NAN, NON_VALID_INPUT}}
   };

    size_t length = sizeof(tests) / sizeof(tests[0]);

    testing_t tresults = {};

    store_data_t storage = {};
    tresults.output = fopen("output.txt", "w");
    tresults.run = &Run;
    tresults.print_message = &PrintMessage;

    for (size_t i = 0; i < length; i++) {
        storage.testing_data = tests[(int) i];
        TestRun(&tresults,(int) i, &storage);
    }
    fclose(tresults.output);
    return 1;
}
