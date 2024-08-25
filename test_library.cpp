#include "test_library.h"

// const char* name
bool TestRun(testing_t *test, int test_number, void *data) {
    test->status = STATE::DEFAULT;
    test->test_number = test_number;
    test->run(test, data);
    test->print_message(test, data);
    return (test->status == STATE::DEFAULT) ? 0 : 1;
}


void TimePrint(FILE *out) {
    time_t mytime = time(NULL);
    struct tm *time = localtime(&mytime);
    fprintf(out, "%02d.%02d.%d %02d:%02d:%02d ",
            time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
            time->tm_hour, time->tm_min,     time->tm_sec);
}


void ChangeStr(const char *s, char *p) {
    size_t len = strlen(s);
    if (len == 0) {
        return;
    }
    size_t j = 0, i = 0;
    p[j++] = '\n';
    p[j++] = '\t';
    for(; i < len; i++) {
        if (s[i] == '\n') {
            p[j++] = '\n';
            p[j++] = '\t';
        }
        else {
            p[j++] = s[i];
        }
    }
    if (s[--i] == '\n') {
        p[--j] = '\0';
    }
    else {
        p[j] = '\0';
    }

}

//logger, условная компиляция для флага с тестами
