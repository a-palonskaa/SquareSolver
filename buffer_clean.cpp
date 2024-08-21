#include "buffer_clean.h"

int BufferClean() {

    int a = 0;
    int symbols = 0;

    while ((a = getchar()) != EOF && a != '\n') {
        if (!isspace(a)) {
        symbols++;
        }
    }
    if (a == EOF) return END_OF_FILE;
    if (symbols != 0) return SYMBOLS_INPUT_ERROR;
    else return NO_ERRORS;
}
