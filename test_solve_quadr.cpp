#include "test_solve_quadr.h"

static void PrintMessage(testing_t* test, void *storage);
static void Run(testing_t *test, void* storage);
static void Log(testing_t *test, enum LOG_LEVEL status, const char *fmt, ...);
void TimePrint(FILE *out);
void ChangeStr(const char *s, char *p);
const char* LogPrint(enum LOG_LEVEL level);

void PrintMessage(testing_t* test, void *storage) {

    store_data_t* data = (store_data_t*)(storage);
    coefficients_t* coeff = &data->testing_data.coefficients;
    roots_t* roots = &data->roots_returned;

    if (test->status == STATE::DEFAULT) {
        Log(test, INFO, "Test No. %d successful \n", test->test_number + 1);
    }
    else if (!(roots->nroots == data->testing_data.roots_expected.nroots)){
        Log(test, ERROR, "Error Test No%d a = %lg, b = %lg, c = %lg \n"
                         "number of root nroots = %d, expected nroots = %d \n",
                         test->test_number + 1,
                         coeff->a, coeff->b, coeff->c,
                         roots->nroots, data->testing_data.roots_expected.nroots);
    }
    else {
        Log(test, ERROR, "Error Test No%d, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg\n"
                         "Expected x1 = %lg, x2 = %lg.\n",
                         test->test_number + 1, coeff->a, coeff->b, coeff->c, roots->x1, roots->x2,
                         data->testing_data.roots_expected.x1, data->testing_data.roots_expected.x2);
    }
}

void Run(testing_t *test, void* storage) {

    store_data_t* data = (store_data_t*)(storage);
    coefficients_t* coeff = &data->testing_data.coefficients;
    roots_t* roots = &data->roots_returned;

    roots->nroots = QuadraticEquation(coeff->a, coeff->b, coeff->c, &roots->x1, &roots->x2);

    ASSERT_EQUAL(test, data->testing_data.roots_expected.nroots, roots->nroots);
    ASSERT_EQUAL_DOUBLE(test, data->testing_data.roots_expected.x1, roots->x1);
    ASSERT_EQUAL_DOUBLE(test, data->testing_data.roots_expected.x2, roots->x2);
}

bool RunAllTests() {

    const testing_data_t tests[]={
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
    tresults.min_level = ERROR;

    for (size_t i = 0; i < length; i++) {
        storage.testing_data = tests[(int) i];
        TestRun(&tresults,(int) i, &storage);
    }
    fclose(tresults.output);
    return 1;
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

//logger, условная компиляция, tester
//аргумкнты командной строки READ
