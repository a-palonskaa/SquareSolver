#include "get_data.h"

int GetData(coefficients_t *quadr_coeff, FILE* file) {
    assert(file != nullptr);
    assert(quadr_coeff != nullptr);

    const int COEFFS_CNT = 3;

    int scanf_results       = 0;
    int bufferclean_results = 0;

    do {
        if (file == stdin) {
            fprintf(stdout, "Enter a, b, c \n");
        }

        static_assert(COEFFS_CNT == 3);
        scanf_results = fscanf(file, "%lg %lg %lg", &(quadr_coeff->a), &(quadr_coeff->b) , &(quadr_coeff->c));

        if (scanf_results == EOF) {
            return INPUT_ERROR;
        }

        if ((bufferclean_results = BufferClean(file)) == END_OF_FILE) {
            return INPUT_ERROR;
        }
    } while (scanf_results != COEFFS_CNT || bufferclean_results == SYMBOLS_INPUT_ERROR);

    return NO_INPUT_ERRORS;
}
