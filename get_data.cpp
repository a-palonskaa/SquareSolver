#include "get_data.h"

int GetData(coefficients_t *quadr_coeff) {

    int flag  = 0;
    int buffer = 0;

    do {
        printf("Enter a, b, c \n");

        flag = scanf("%lg %lg %lg", &(quadr_coeff->a), &(quadr_coeff->b) , &(quadr_coeff->c));

        if (flag == EOF) {
            return INPUT_ERROR;
        }

        if ((buffer = BufferClean()) == END_OF_FILE) {
            return INPUT_ERROR;
        }

    } while (flag != 3 || buffer == SYMBOLS_INPUT_ERROR);

    return NO_INPUT_ERRORS;
}
