#include "arg_parser.h"

/**
 * @brief  Change mode of operation to the test mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
#ifdef TESTING
static enum ERRORS ChangeFlagModeTest(flags_t *flags, const char* arg);
#endif

/**
 * @brief  Change mode of operation to the solve mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum ERRORS ChangeFlagModeSolve(flags_t *flags, const char* arg);

/**
 * @brief  Change input mode to the input in console mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum ERRORS ChangeFlagInputConsole(flags_t *flags, const char* arg);

/**
 * @brief  Change input mode to the input in file mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum ERRORS ChangeFlagInputFile(flags_t *flags, const char* arg);

/**
 * @brief  Change output mode to the output in console mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum ERRORS ChangeFlagOutputConsole(flags_t *flags, const char* arg);

/**
 * @brief  Change output mode to the output in file mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum ERRORS ChangeFlagOutputFile(flags_t *flags, const char* arg);

/**
 * @brief  Change mode of the operation to the help mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum ERRORS Help(flags_t *flags, const char* argv);

/**
 * @brief  Print information about commands
 */
static void PrintHelp();

/**
 * @brief  Validate the commands input
 * @param[in] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
enum ERRORS ValidateInput(flags_t *flags);

const option_t commands[] = {
    //   short_name      long_name      changeflag function                  description     has_arg
#ifdef TESTING
        {"-t",           "--test",      &ChangeFlagModeTest,                 "Testing mode", false},
#endif
        {"-s",          "--solve",     &ChangeFlagModeSolve,                 "Solving mode", false},
        {"-c",  "--input_console",  &ChangeFlagInputConsole,   "Read data from the console", false},
        {"-i",     "--input_file",     &ChangeFlagInputFile,      "Read data from the file",  true},
        {"-f", "--output_console", &ChangeFlagOutputConsole, "Print results in the console", false},
        {"-o",         "--output",    &ChangeFlagOutputFile,   "Print results in the file ",  true},
        {"-h",           "--help",                    &Help,                         "Help", false}
};

const size_t length = sizeof(commands) / sizeof(commands[0]);

int ArgParser(int argc, const char *argv[], flags_t *flags) {
    if (argc > 0) {
        while (--argc > 0) {
            argv++;
            int flag = 0;

            for (size_t i = 0; i < length; i++) {
                if(!(strcmp(*argv, commands[i].name) &&
                    strcmp(*argv, commands[i].long_name))) {

                    flag++;

                    if (commands[i].has_arg && argc <= 1) {
                        PrintHelp();
                        return INPUT_ERROR;
                    }

                    enum ERRORS state = NO_ERRORS;

                    if (!commands[i].has_arg) {
                        state = commands[i].change(flags, nullptr);
                    }
                    else {
                        argc--;
                        state = commands[i].change(flags, *++argv);
                    }

                    if (state == INPUT_ERROR) {
                        printf(RED("ERROR OF COMMAND \n"));
                        return INPUT_ERROR;
                    }
                }
            }
            if (!flag) {
                printf(RED("UNKNOWN COMMAND \n"));
                return INPUT_ERROR;
            }
        }
        return ValidateInput(flags);
    }
    else {
        return INPUT_ERROR;
    }

}

enum ERRORS ChangeFlagModeSolve(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->mode = SOLVE;
    flags->mode_valid++;
    return NO_ERRORS;
}

#ifdef TESTING
enum ERRORS ChangeFlagModeTest(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->mode = TEST;
    flags->mode_valid++;
    return NO_ERRORS;
}
#endif

enum ERRORS ChangeFlagInputConsole(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->input = INPUT_FLAGS::CONSOLE;
    flags->input_valid++;
    return NO_ERRORS;
}

enum ERRORS ChangeFlagInputFile(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->input = INPUT_FLAGS::FILE;
    flags->input_valid++;
    flags->file_input = arg;
    if (!strcmp(flags->file_input, "stdin")) {
        flags->input = INPUT_FLAGS::CONSOLE;
    }
    return NO_ERRORS;
}

enum ERRORS ChangeFlagOutputConsole(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->output = OUTPUT_FLAGS::CONSOLE;
    flags->output_valid++;
    return NO_ERRORS;
}

enum ERRORS ChangeFlagOutputFile(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->output = OUTPUT_FLAGS::FILE;
    flags->output_valid++;
    flags->file_output = arg;
    if (!strcmp(flags->file_output, "stdout")) {
        flags->output = OUTPUT_FLAGS::CONSOLE;
    }
    return NO_ERRORS;
}

enum ERRORS Help(flags_t *flags, const char* arg) {
    (void) arg;
    (void) flags;

    PrintHelp();
    return INPUT_ERROR;
}

void PrintHelp() {
    for (size_t i = 0; i < length; i++) {
        printf("%10s %10s %-10s \n", commands[i].name, commands[i].long_name, commands[i].description);
    }
}

enum ERRORS ValidateInput(flags_t *flags) {
    assert(flags != nullptr);

#ifdef TESTING
    if (flags->mode_valid > 1) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
#endif

    if (flags->output_valid > 1 ||
        flags->input_valid  > 1) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
    return NO_ERRORS;
}

void InitiallizeFlags(flags_t *flags) {
    flags->mode   =                 SOLVE;
    flags->output = OUTPUT_FLAGS::CONSOLE;
    flags->input  =  INPUT_FLAGS::CONSOLE;

    flags->mode_valid   = 0;
    flags->output_valid = 0;
    flags->input_valid  = 0;
}
