#include "arg_parser.h"

static int ChangeFlagMode  (flags_t *flags, int *argc, const char *argv[]);
static int ChangeFlagInput (flags_t *flags, int *argc, const char *argv[]);
static int ChangeFlagOutput(flags_t *flags, int *argc, const char *argv[]);

const option_t commands[] = { {"-t",            "Testing mode",   &ChangeFlagMode},
                              {"-i", "Read data from the file",  &ChangeFlagInput},
                              {"-o",             "Print data ", &ChangeFlagOutput}
};

int ArgParser(int *argc, const char *argv[], flags_t *flags) {
    size_t length = sizeof(commands) / sizeof(commands[0]);
    while (--(*argc) > 0) {
        argv++;
        for (size_t i = 0; i < length; i++) {
            if(!strcmp(*argv, commands[i].name)) {
                if (commands[i].change(flags, argc, argv) == INPUT_ERROR) {
                    printf("ERROR OF COMMAND \n");
                    return INPUT_ERROR;
                }
            }
        }
    }
    return NO_ERRORS;
}

int ChangeFlagMode(flags_t *flags, int *argc, const char *argv[]) {
    (void) argc;
    (void) argv;
    flags->mode = TEST;
    return NO_ERRORS;
}
int ChangeFlagInput(flags_t *flags, int *argc, const char *argv[]) {
    flags->input = INPUT_FLAGS::FILE;
    flags->file_input = *++argv;
    (*argc)--;
    if (*argc == 0) {
        return INPUT_ERROR;
    }
    return NO_ERRORS;
}

int ChangeFlagOutput(flags_t *flags, int *argc, const char *argv[]) {
    flags->output = OUTPUT_FLAGS::FILE;
    flags->file_output = *++argv;
    (*argc)--;
    if (*argc == 0) {
        return INPUT_ERROR;
    }
    return NO_ERRORS;
}
