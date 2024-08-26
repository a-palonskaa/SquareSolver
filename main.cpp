#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define_consts.h"
#include "buffer_clean.h"
#include "get_data.h"
#include "solve_quadr.h"
#include "show_results.h"
#ifndef NO_TEST
#include "test_solve_quadr.h"
#endif
#include "arg_parser.h"

int main(int argc, const char *argv[]) {

    flags_t flags = {};
    InitiallizeFlags(&flags);

    if (ArgParser(argc, argv, &flags) == INPUT_ERROR) {
        return EXIT_FAILURE;
    }

    FILE *file_in  = (flags.input  ==  INPUT_FLAGS::CONSOLE) ? stdin  :  fopen(flags.file_input, "r");
    if (file_in == NULL) {
        perror(RED("FAILED TO OPEN INPUT FILE \n"));
        return EXIT_FAILURE;
    }
    FILE *file_out = (flags.output == OUTPUT_FLAGS::CONSOLE) ? stdout : fopen(flags.file_output, "w");
    if (file_out == NULL) {
        perror(RED("FAILED TO OPEN OUTPUT FILE \n"));
        return EXIT_FAILURE;
    }

    LoggerSetLevel(INFO);
    LoggerSetFile(file_out);

    fprintf(file_out, "Quadratic equation solver \n"); //TODO: не выводить в режиме тестов

    coefficients_t coefficients = {};

#ifndef NO_TEST
    if (flags.mode == TEST) {
        int status = RunAllTests();
        fclose(file_out);
        return status;
    }
#endif

    int status = GetData(&coefficients, file_in);
    if (status == INPUT_ERROR) {
        fprintf(file_out, "INPUT ERROR");
        fclose(file_out);
        return EXIT_FAILURE;
    }

    double x1 = 0, x2 = 0;

    enum NUM_ROOTS nroots = QuadraticEquation(coefficients.a, coefficients.b, coefficients.c, &x1, &x2);

    ShowResults(nroots, x1, x2, file_out);
    fclose(file_out);

    return EXIT_SUCCESS;
}

