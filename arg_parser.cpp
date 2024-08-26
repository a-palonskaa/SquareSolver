#include "arg_parser.h"

/**
 * @brief  Change mode of operation to the test mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
#ifndef NO_TEST
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

int ArgParser(int argc, const char *argv[], flags_t *flags) {
    while (--argc > 0) {
        argv++;
        for (size_t i = 0; i < length; i++) {
            if(!(strcmp(*argv, commands[i].name) &&
                 strcmp(*argv, commands[i].long_name))) {

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

                break;
            }
        }
    }
    return ValidateInput(flags);
}

enum ERRORS ChangeFlagModeSolve(flags_t *flags, const char* arg) {
    (void) arg;
    flags->mode = SOLVE;
    flags->mode_valid++;
    return NO_ERRORS;
}

#ifndef NO_TEST
enum ERRORS ChangeFlagModeTest(flags_t *flags, const char* arg) {
    (void) arg;
    flags->mode = TEST;
    flags->mode_valid++;
    return NO_ERRORS;
}
#endif

enum ERRORS ChangeFlagInputConsole(flags_t *flags, const char* arg) {
    (void) arg;
    flags->input = INPUT_FLAGS::CONSOLE;
    flags->input_valid++;
    return NO_ERRORS;
}

enum ERRORS ChangeFlagInputFile(flags_t *flags, const char* arg) {
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
    (void) arg;
    flags->output = OUTPUT_FLAGS::CONSOLE;
    flags->output_valid++;
    return NO_ERRORS;
}

enum ERRORS ChangeFlagOutputFile(flags_t *flags, const char* arg) {
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
        printf("%10s %10s  %-10s \n", commands[i].name, commands[i].long_name, commands[i].description);
    }
}

enum ERRORS ValidateInput(flags_t *flags) {

#ifndef NO_TEST
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
    flags->mode          =                 SOLVE;
    flags->output        = OUTPUT_FLAGS::CONSOLE;
    flags->input         =  INPUT_FLAGS::CONSOLE;
    flags->mode_valid    =   0;
    flags->output_valid  =   0;
    flags->input_valid   =   0;
}
