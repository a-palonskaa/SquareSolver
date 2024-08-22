#include "test_library.h"

// const char* name
void TestRun(testing_t *test, int test_number, void *data) {
    test->status = DEFAULT;
    test->test_number = test_number;
    bool flag = test->run(test, data);
    (void) flag;
}

// Список вспомогательных функций:
// Assert Equal // кладет тест
// Check Equal // не кладёт тест, но помечает неверным
// TestRun // инициализирует тест и вызывает run
// Log (сообщение в файл через ..., vargs)
//покрасить вывод



