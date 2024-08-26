#include "test_library.h"

// const char* name
bool TestRun(testing_t *test, int test_number, void *data) {
    test->status = STATE::DEFAULT;
    test->test_number = test_number;
    test->run(test, data);
    test->print_message(test, data);
    return test->status != STATE::DEFAULT;
}


void TimePrint(FILE *out) {
    time_t mytime = time(NULL);
    struct tm *time = localtime(&mytime);
    fprintf(out, "%02d.%02d.%d %02d:%02d:%02d ",
            time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
            time->tm_hour, time->tm_min,     time->tm_sec);
}


void AestheticizeString(const char *src, char *dst, size_t max_len) {
    size_t len = strlen(src);
    if (len == 0) {
        return;
    }
    size_t j = 0, i = 0;
    dst[j++] = '\n';
    dst[j++] = '\t';
    for(; i < len && j < max_len - 1; i++) {
        if (src[i] == '\n') {
            dst[j++] = '\n';
            dst[j++] = '\t';
        }
        else {
            dst[j++] = src[i];
        }
    }
    if (src[--i] == '\n') {
        dst[--j] = '\0';
    }
    else {
        dst[j] = '\0';
    }

}
