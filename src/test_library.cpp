#include "test_library.h"

bool TestRun(testing_t *test, int test_number, void *data) {
    assert(data != nullptr);
    assert(test != nullptr);

    test->status = State::DEFAULT;
    test->test_number = test_number;
    test->test_execute(test, data);
    test->print_message(test, data);

    return test->status != State::DEFAULT;
}
