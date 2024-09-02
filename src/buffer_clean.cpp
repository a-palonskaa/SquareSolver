#include "buffer_clean.h"

int BufferClean(FILE* file) {
    assert(file != nullptr);

    int symbol     = 0;
    int symbol_cnt = 0;

    while ((symbol = fgetc(file)) != EOF && symbol != '\n') {
        if (!isspace(symbol)) {
            symbol_cnt++;
        }
    }

    return symbol == EOF   ? END_OF_FILE :
           symbol_cnt != 0 ? SYMBOLS_INPUT_ERROR :
                             NO_ERRORS;
}
