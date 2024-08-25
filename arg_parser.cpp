#include "arg_parser.h"

typedef const char** argv_t;

#ifndef NO_TEST
static int ChangeFlagModeTest(flags_t *flags, int *argc, argv_t* argv);
#endif
static int ChangeFlagModeSolve(flags_t *flags, int *argc, argv_t* argv);
static int ChangeFlagInputConsole(flags_t *flags, int *argc, argv_t* argv);
static int ChangeFlagInputFile(flags_t *flags, int *argc, argv_t* argv);
static int ChangeFlagOutputConsole(flags_t *flags, int *argc, argv_t* argv);
static int ChangeFlagOutputFile(flags_t *flags, int *argc, argv_t* argv);
static int Help(flags_t *flags, int *argc, argv_t* argv);
enum ERRORS ValidateInput(flags_t *flags);
static void PrintHelp(void);


const option_t commands[] = {
#ifndef NO_TEST
        {"-t",           "--test",                  &ChangeFlagModeTest,                 "Testing mode", 0},
#endif
        {"-s",          "--solve",                 &ChangeFlagModeSolve,                 "Solving mode", 0},
        {"-c",  "--input_console",              &ChangeFlagInputConsole,   "Read data from the console", 0},
        {"-i",     "--input_file",                 &ChangeFlagInputFile,      "Read data from the file", 1},
        {"-f", "--output_console",             &ChangeFlagOutputConsole, "Print results in the console", 0},
        {"-o",         "--output",                &ChangeFlagOutputFile,   "Print results in the file ", 1},
        {"-h",           "--help",                                &Help,                         "Help", 0}
};

const size_t length = sizeof(commands) / sizeof(commands[0]);

int ArgParser(int *argc, const char *argv[], flags_t *flags) {
    while (--(*argc) > 0) {
        argv++;
        for (size_t i = 0; i < length; i++) {
            if(!(strcmp(*argv, commands[i].name) &&
                 strcmp(*argv, commands[i].long_name))) {
                if (commands[i].has_arg && *argc <= 1) {
                    PrintHelp();
                    return INPUT_ERROR;
                }
                if (commands[i].change(flags, argc, &argv) == INPUT_ERROR) {
                    printf(RED("ERROR OF COMMAND \n"));
                    return INPUT_ERROR;
                }
                break;
            }
        }
    }
    return ValidateInput(flags);
}

int ChangeFlagModeSolve(flags_t *flags, int *argc, argv_t* argv) {
    (void) argc;
    (void) argv;
    flags->mode = SOLVE;
    flags->mode_solve_valid = VALIDATION::ACTIVE;
    return NO_ERRORS;
}

#ifndef NO_TEST
int ChangeFlagModeTest(flags_t *flags, int *argc, argv_t* argv) {
    (void) argc;
    (void) argv;
    flags->mode = TEST;
    flags->mode_test_valid = VALIDATION::ACTIVE;
    return NO_ERRORS;
}
#endif

int ChangeFlagInputConsole(flags_t *flags, int *argc, argv_t* argv) {
    (void) argc;
    (void) argv;
    flags->input = INPUT_FLAGS::FILE;
    flags->input_console_valid = VALIDATION::ACTIVE;
    return NO_ERRORS;
}

int ChangeFlagInputFile(flags_t *flags, int *argc, argv_t* argv) {
    flags->input = INPUT_FLAGS::FILE;
    flags->input_file_valid = VALIDATION::ACTIVE;
    (*argc)--;
    flags->file_input = *++(*argv);
    if (!strcmp(flags->file_input, "stdin")) {
        flags->input = INPUT_FLAGS::CONSOLE;
    }
    return NO_ERRORS;
}


int ChangeFlagOutputConsole(flags_t *flags, int *argc, argv_t* argv) {
    (void) argc;
    (void) argv;
    flags->output = OUTPUT_FLAGS::FILE;
    flags->output_console_valid = VALIDATION::ACTIVE;
    return NO_ERRORS;
}

int ChangeFlagOutputFile(flags_t *flags, int *argc, argv_t* argv) {
    flags->output = OUTPUT_FLAGS::FILE;
    flags->output_file_valid = VALIDATION::ACTIVE;
    (*argc)--;
    flags->file_output = *++(*argv);
    if (!strcmp(flags->file_output, "stdout")) {
        flags->output = OUTPUT_FLAGS::CONSOLE;
    }
    return NO_ERRORS;
}

int Help(flags_t *flags, int *argc, argv_t* argv) {
    (void) argc;
    (void) argv;
    (void) flags;
    PrintHelp();
    return INPUT_ERROR;
}

void PrintHelp() {
    for (size_t i = 0; i < length; i++) {
        printf("%10s %10s  %-10s \n", commands[i].name, commands[i].long_name, commands[i].description);
    }
}

enum ERRORS ValidateInput(flags_t *flags) {
#ifndef NO_TEST
    if (flags->mode_test_valid == VALIDATION::ACTIVE &&
        flags->mode_solve_valid == VALIDATION::ACTIVE) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
#endif
    if (flags->output_console_valid == VALIDATION::ACTIVE &&
        flags->output_file_valid == VALIDATION::ACTIVE) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
    if (flags->input_console_valid == VALIDATION::ACTIVE &&
        flags->input_file_valid == VALIDATION::ACTIVE) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
    return NO_ERRORS;
}


void InitiallizeFlags(flags_t *flags) {
    flags->mode                 =                 SOLVE;
    flags->output               = OUTPUT_FLAGS::CONSOLE;
    flags->input                =  INPUT_FLAGS::CONSOLE;
    flags->mode_test_valid      =   VALIDATION::DEFAULT;
    flags->mode_solve_valid     =   VALIDATION::DEFAULT;
    flags->output_file_valid    =   VALIDATION::DEFAULT;
    flags->output_console_valid =   VALIDATION::DEFAULT;
    flags->input_file_valid     =   VALIDATION::DEFAULT;
    flags->input_console_valid  =   VALIDATION::DEFAULT;
}
