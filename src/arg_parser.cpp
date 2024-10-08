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
static enum Errors ChangeFlagModeTest(flags_t *flags, const char* arg);
#endif

/**
 * @brief  Change mode of operation to the solve mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum Errors ChangeFlagModeSolve(flags_t *flags, const char* arg);

/**
 * @brief  Change input mode to the input in console mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum Errors ChangeFlagInputConsole(flags_t *flags, const char* arg);

/**
 * @brief  Change input mode to the input in file mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum Errors ChangeFlagInputFile(flags_t *flags, const char* arg);

/**
 * @brief  Change output mode to the output in console mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum Errors ChangeFlagOutputConsole(flags_t *flags, const char* arg);

/**
 * @brief  Change output mode to the output in file mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum Errors ChangeFlagOutputFile(flags_t *flags, const char* arg);

/**
 * @brief  Change mode of the operation to the help mode
 * @param[in]  arg   Poiner to the beginning of the command line argument(name of file)
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
static enum Errors Help(flags_t *flags, const char* argv);

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
enum Errors ValidateInput(const flags_t *flags);

const option_t COMMANDS[] = {
    //   short_name      long_name      changeflag function                  description     has_arg
#ifdef TESTING
        {"-t",           "--test",      &ChangeFlagModeTest,                 "Testing mode", false},
#endif
        {"-s",          "--solve",     &ChangeFlagModeSolve,                 "Solving mode", false},
        {"-c",  "--input-console",  &ChangeFlagInputConsole,   "Read data from the console", false},
        {"-i",     "--input-file",     &ChangeFlagInputFile,      "Read data from the file",  true},
        {"-f", "--output-console", &ChangeFlagOutputConsole, "Print results in the console", false},
        {"-o",         "--output",    &ChangeFlagOutputFile,   "Print results in the file ",  true},
        {"-h",           "--help",                    &Help,                         "Help", false}
};

const size_t COMMANDS_ARRAY_LENGTH = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

int ArgParser(int argc, const char *argv[], flags_t *flags) {
    assert(argv  != nullptr);
    assert(flags != nullptr);
    assert(argc >= 0);

    if (argc == 0) {
        return INPUT_ERROR;
    }

    while (--argc > 0) {
        argv++;
        int has_arg_validate = 0;

        for (size_t i = 0; i < COMMANDS_ARRAY_LENGTH; i++) {
            if(!(strcmp(*argv, COMMANDS[i].name) &&
                    strcmp(*argv, COMMANDS[i].long_name))) {

                has_arg_validate++;

                if (COMMANDS[i].has_arg && argc <= 1) {
                    PrintHelp();
                    return INPUT_ERROR;
                }

                enum Errors state = NO_ERRORS;

                if (!COMMANDS[i].has_arg) {
                    state = COMMANDS[i].change(flags, nullptr);
                }
                else {
                    argc--;
                    state = COMMANDS[i].change(flags, *++argv);
                }

                if (state == INPUT_ERROR) {
                    printf(RED("ERROR OF COMMAND \n"));
                    return INPUT_ERROR;
                }
            }
        }
        if (!has_arg_validate) {
            printf(RED("UNKNOWN COMMAND \n"));
            return INPUT_ERROR;
        }
    }
    return ValidateInput(flags);
}

enum Errors ChangeFlagModeSolve(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->mode = ModeFlags::SOLVE;
    flags->mode_valid++;
    return NO_ERRORS;
}

#ifdef TESTING
enum Errors ChangeFlagModeTest(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->mode = ModeFlags::TEST;
    flags->mode_valid++;
    return NO_ERRORS;
}
#endif

enum Errors ChangeFlagInputConsole(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->input = InputFlag::CONSOLE;
    flags->input_valid++;
    return NO_ERRORS;
}

enum Errors ChangeFlagInputFile(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->input = InputFlag::FILE;
    flags->input_valid++;
    flags->file_input = arg;
    if (!strcmp(flags->file_input, "stdin")) {
        flags->input = InputFlag::CONSOLE;
    }
    return NO_ERRORS;
}

enum Errors ChangeFlagOutputConsole(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->output = OutputFlags::CONSOLE;
    flags->output_valid++;
    return NO_ERRORS;
}

enum Errors ChangeFlagOutputFile(flags_t *flags, const char* arg) {
    assert(flags != nullptr);
    (void) arg;

    flags->output = OutputFlags::FILE;
    flags->output_valid++;
    flags->file_output = arg;

    if (!strcmp(flags->file_output, "stdout")) {
        flags->output = OutputFlags::CONSOLE;
    }
    return NO_ERRORS;
}

enum Errors Help(flags_t *flags, const char* arg) {
    (void) arg;
    (void) flags;

    PrintHelp();
    return INPUT_ERROR;
}

void PrintHelp() {
    for (size_t i = 0; i < COMMANDS_ARRAY_LENGTH; i++) {
        printf("%10s %10s %-10s" "\n", COMMANDS[i].name,
                                       COMMANDS[i].long_name,
                                       COMMANDS[i].description);
    }
}

enum Errors ValidateInput(const flags_t *flags) {
    assert(flags != nullptr);

#ifdef TESTING
    if (flags->mode_valid > 1) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
#endif

    if (flags->output_valid > 1 ||
        flags-> input_valid > 1) {
        printf(RED("MUTUAL DESTRUCTION ERROR \n"));
        return INPUT_ERROR;
    }
    return NO_ERRORS;
}

void InitiallizeFlags(flags_t *flags) {
    flags->mode   =   ModeFlags::  SOLVE;
    flags->output = OutputFlags::CONSOLE;
    flags->input  =  InputFlag::CONSOLE;

    flags->mode_valid   = 0;
    flags->output_valid = 0;
    flags->input_valid  = 0;
}
