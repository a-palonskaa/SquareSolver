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

int main(int argc, char *argv[]) {

    enum FLAGS flag_mode             = SOLVE;                  //default status solve mode
    enum OUTPUT_FLAGS flag_output    = OUTPUT_FLAGS::CONSOLE;  // default status print to console
    enum INPUT_FLAGS  flag_input     = INPUT_FLAGS::CONSOLE;   // default status read from console
    char file_input[MAXLINE]  = {};
    char file_output[MAXLINE] = {};

//в функцию arg parser
//getopt
//функции в структуре меняю флаги
    ArgParser(argc, (const char**) argv, &flag_mode, &flag_output, &flag_input, file_input, file_output);
    /* while (--argc > 0) {
        argv++;
        if (!strcmp(*argv, "-t")) {           //testing mode
            flag_mode = TEST;
        }
        if (!strcmp(*argv, "-i")) {           //read a name of the file to read the data from
            flag_input = INPUT_FLAGS::FILE;
            strcpy(file_input, *++argv);
            argc--;
        }
        if (!strcmp(*argv, "-o")) {            //read a name of the file to print the results
            flag_output = OUTPUT_FLAGS::FILE;
            strcpy(file_output, *++argv);
            argc--;
        }
    }
*/
    FILE *file_in = (flag_input == INPUT_FLAGS::CONSOLE) ? stdin : fopen(file_input, "r");
    FILE *file_out = (flag_output == OUTPUT_FLAGS::CONSOLE) ? stdout : fopen(file_output, "w");

    fprintf(file_out, "Quadratic equation solver \n");

    coefficients_t quadr = {};

    if (flag_mode == TEST) {
        int state = RunAllTests();
        (void) state;
        return EXIT_SUCCESS;
    }


    int status = GetData(&quadr, file_in);
    if (status == INPUT_ERROR) {
        fprintf(file_out, "INPUT ERROR");
        fclose(file_out);
        return EXIT_FAILURE;
    }

    double x1 = 0, x2 = 0;

    enum NUM_ROOTS nroots = QuadraticEquation(quadr.a, quadr.b, quadr.c, &x1, &x2);

    ShowResults(nroots, x1, x2, file_out);

    return EXIT_SUCCESS;
}

