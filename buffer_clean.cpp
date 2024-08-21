#include "buffer_clean.h"

int BufferClean() {

    int a = 0;

    while ((a = getchar()) != EOF && a != '\n') {
        ;
    }

    return (a != EOF);
}
