#include "buffer_clean.h"

int BufferClean() {

    int a = 0;

    while ((a = getchar()) != EOF && a != '\n') {
        ;
    }

    return (a != EOF);
}
// TODO: пропускать если пробелы isspace(), если после еще есть символы- ошибка, eof детектить
