#include "test_library.h"

// const char* name
void TestRun(testing_t *test, int test_number, void *data) {
    test->status = STATE::DEFAULT;
    test->test_number = test_number;
    test->run(test, data);
    test->print_message(test, data);
}

// Список вспомогательных функций:
// Assert Equal // кладет тест
// Check Equal // не кладёт тест, но помечает неверным
// TestRun // инициализирует тест и вызывает run
// Log (сообщение в файл через ..., vargs)
//покрасить вывод

/*
Log(test, "message %d", 5);
Log(test, "message");
 */
