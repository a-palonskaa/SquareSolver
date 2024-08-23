#include "arg_parser.h"


void ArgParser(int argc, const char *argv[],
               enum FLAGS *flag_mode, enum OUTPUT_FLAGS *flag_output, enum INPUT_FLAGS  *flag_input,
               char *file_input, char *file_output) {
    while (--argc > 0) {
        argv++;
        if (!strcmp(*argv, "-t")) {           //testing mode
            *flag_mode = TEST;
        }
        if (!strcmp(*argv, "-i")) {           //read a name of the file to read the data from
            *flag_input = INPUT_FLAGS::FILE;
            strcpy(file_input, *++argv);
            argc--;
        }
        if (!strcmp(*argv, "-o")) {            //read a name of the file to print the results
            *flag_output = OUTPUT_FLAGS::FILE;
            strcpy(file_output, *++argv);
            argc--;
        }
    }

}
