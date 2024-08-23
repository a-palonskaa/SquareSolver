#include "buffer_clean.h"

int BufferClean(FILE* file) {

    int a       = 0;
    int symbols = 0;

    while ((a = getc(file)) != EOF && a != '\n') {
        if (!isspace(a)) {
            symbols++;
        }
    }

    return a == EOF     ? END_OF_FILE :
           symbols != 0 ? SYMBOLS_INPUT_ERROR :
                          NO_ERRORS;
}
