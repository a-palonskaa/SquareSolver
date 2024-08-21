#include "get_data.h"

int GetData(struct Coeff *pointer) { // TODO: переименовать pointer

    int flag  = 0;
    int bufer = 0;

    do {
        printf("Enter a, b, c \n");

        flag = scanf("%lg %lg %lg", &(pointer->a), &(pointer->b) , &(pointer->c));

        if (flag == EOF) {
            return INPUT_ERROR;
        }

        if ((bufer = BufferClean()) == END_OF_FILE) {
            return INPUT_ERROR;
        }

    } while (flag != 3 || bufer == SYMBOLS_INPUT_ERROR);

    return 1;
}
