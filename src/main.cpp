#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define_consts.h"
#include "get_data.h"
#include "solve_quadr.h"
#include "show_results.h"
#include "logger.h"
#include "arg_parser.h"

#ifdef TESTING
#include "test_solve_quadr.h"
#endif

int main(int argc, const char *argv[]) {
    flags_t flags = {};
    InitiallizeFlags(&flags);

    if (ArgParser(argc, argv, &flags) == INPUT_ERROR) {
        return EXIT_FAILURE;
    }

    FILE *file_in  = (flags.input  ==  INPUT_FLAGS::CONSOLE) ? stdin  :  fopen(flags.file_input, "r");
    if (file_in == nullptr) {
        perror(RED("FAILED TO OPEN INPUT FILE \n"));
        return EXIT_FAILURE;
    }

    FILE *file_out = (flags.output == OUTPUT_FLAGS::CONSOLE) ? stdout : fopen(flags.file_output, "w");
    if (file_out == nullptr) {
        perror(RED("FAILED TO OPEN OUTPUT FILE \n"));
        return EXIT_FAILURE;
    }

    LoggerSetLevel(INFO);
    LoggerSetFile(file_out);

#ifdef TESTING
    if (flags.mode == TEST) {
        int status = RunAllTests();
        fclose(file_out);
        return status;
    }
#endif

    fprintf(file_out, "Quadratic equation solver \n");
    coefficients_t coefficients = {};

    int status = GetData(&coefficients, file_in);
    if (status == INPUT_ERROR) {
        fprintf(file_out, "INPUT ERROR");

        if (fclose(file_out) == EOF ) {
            perror(RED("FAILED TO CLOSE OUTPUT FILE \n"));
        }

        if (fclose(file_in) == EOF ) {
            perror(RED("FAILED TO CLOSE OUTPUT FILE \n"));
        }

        return EXIT_FAILURE;
    }

    double x1 = 0, x2 = 0;

    enum NUM_ROOTS nroots = QuadraticEquation(coefficients.a, coefficients.b, coefficients.c, &x1, &x2);

    ShowResults(nroots, x1, x2, file_out);

    if (fclose(file_out) == EOF ) {
            perror(RED("FAILED TO CLOSE OUTPUT FILE \n"));
        }

    if (fclose(file_in) == EOF ) {
            perror(RED("FAILED TO CLOSE OUTPUT FILE \n"));
        }

    return EXIT_SUCCESS;
}

