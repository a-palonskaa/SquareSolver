#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define_consts.h"
#include "buffer_clean.h"
#include "get_data.h"
#include "solve_quadr.h"
#include "show_results.h"
#include "test_solve_quadr.h"
#include "arg_parser.h"

int main(int argc, const char *argv[]) {

    flags_t flags   =                    {};
    flags.mode      =                 SOLVE;
    flags.output    = OUTPUT_FLAGS::CONSOLE;
    flags.input     =  INPUT_FLAGS::CONSOLE;

    if (ArgParser(&argc, argv, &flags) == INPUT_ERROR) {
        return EXIT_FAILURE;
    }

    FILE *file_in  = (flags.input  ==  INPUT_FLAGS::CONSOLE) ? stdin  :  fopen(flags.file_input, "r");
    FILE *file_out = (flags.output == OUTPUT_FLAGS::CONSOLE) ? stdout : fopen(flags.file_output, "w");

    if (file_in == NULL) {
        printf("FAILED TO OPEN INPUT FILE \n"); //perror instead of printf и между файлопен вставить
        return EXIT_FAILURE;
    }

    if (file_out == NULL) {
        printf("FAILED TO OPEN OUTPUT FILE \n");
        return EXIT_FAILURE;
    }

    fprintf(file_out, "Quadratic equation solver \n");

    coefficients_t coefficients = {};

    if (flags.mode == TEST) {
        int state = RunAllTests();
        (void) state;
        return EXIT_SUCCESS; // TODO: return state ....
    }

    int status = GetData(&coefficients, file_in);
    if (status == INPUT_ERROR) {
        fprintf(file_out, "INPUT ERROR");
        fclose(file_out);
        return EXIT_FAILURE;
    }

    double x1 = 0, x2 = 0;

    enum NUM_ROOTS nroots = QuadraticEquation(coefficients.a, coefficients.b, coefficients.c, &x1, &x2);

    ShowResults(nroots, x1, x2, file_out);

    return EXIT_SUCCESS;
}

