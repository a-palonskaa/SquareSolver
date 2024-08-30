#include "test_library.h"

bool TestRun(testing_t *test, int test_number, void *data) {
    assert(data != nullptr);
    assert(test != nullptr);

    test->status = STATE::DEFAULT;
    test->test_number = test_number;
    test->run(test, data);
    test->print_message(test, data);

    return test->status != STATE::DEFAULT;
}
