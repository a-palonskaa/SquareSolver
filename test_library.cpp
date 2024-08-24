#include "test_library.h"

// const char* name
void TestRun(testing_t *test, int test_number, void *data) {
    test->status = STATE::DEFAULT;
    test->test_number = test_number;
    test->run(test, data);
    test->print_message(test, data);
}


void Log(testing_t *test, enum LOG_LEVEL status, const char *fmt, ...) {
    char s[MAXLINE] = "";
    char p[MAXLINE] = "";
    strcpy(s, fmt);
    ChangeStr(s, p);
    va_list args;
    va_start (args, fmt);
    if (test->min_level <= status) {
        fprintf(test->output, "%s", LogPrint (status));
        TimePrint(test->output);
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
    vfprintf (test->output, p, args);
#pragma clang diagnostic pop

    va_end (args);
}

void TimePrint(FILE *out) {
    time_t mytime = time(NULL);
    struct tm *time = localtime(&mytime);
    fprintf(out, "%02d.%02d.%d %02d:%02d:%02d ",
            time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
            time->tm_hour, time->tm_min,     time->tm_sec);
}

const char* LogPrint (enum LOG_LEVEL level) {
    switch (level) {
        case ERROR:
            return "[ERROR] ";
        case WARNING:
            return "[WARNING] ";
        case INFO:
            return "[INFO] ";
        case DEBUG:
            return "[DEBUG] ";
        default:
            break;
        }

    return "!ERROR! ";
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

// arg_parse
//logger, условная компиляция
//покрасить вывод
