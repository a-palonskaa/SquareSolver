/**
 * @file arg_parser.h
 * @brief Determine the program operation mode
 */
#ifndef ARG_PARSER
#define ARG_PARSER

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "print_colors.h"
#include "define_consts.h"

/**
 * @brief enum for the status of the mode
 */
enum class ModeFlags {
    SOLVE = 0,   ///< mode of solving quardatic equation
    TEST  = 1    ///< mode of testing the algorithm of solving quadratic equation
};

/**
 * @brief enum for the status of the output
 */
enum class OutputFlags {
    CONSOLE = 0,  ///< mode of printing results in the console
    FILE    = 1   ///< mode of printing results in the file
};

/**
 * @brief enum for the status of the input
 */
enum class InputFlag {
    CONSOLE = 0,  ///< mode of reading data from the console
    FILE    = 1   ///< mode of reading data from the file
};

/** @struct flags_t
 * @brief Structure for flags of commands
 * @var flags_t::mode
 * Member 'mode' is a default status solve mode
 * @var flags_t::output
 * Member 'output' is a default status print to console
 * @var flags_t::mode_valid
 * Member 'mode_valid' is a counter for mode changes
 * @var flags_t::input_valid
 * Member 'input_valid' is a counter for input changes
 * @var flags_t::output_valid
 * Member 'output_valid' is a counter for output changes
 * @var flags_t::file_input
 * Member 'file_input' is a pointer to the string with input file name
 * @var flags_t::file_output
 * Member 'file_output' is a pointer to the string with output file name
 */
typedef struct {
    enum ModeFlags   mode;
    enum OutputFlags output;
    enum InputFlag  input;

    int mode_valid;
    int input_valid;
    int output_valid;

    const char* file_input;
    const char* file_output;
} flags_t;

/**
 * @brief  Define the mode in which the program orepates
 * @param[in]  argc   Number of arguments of the command line
 * @param[in]  argv   Poiner to the array of the arguments of the command line
 * @param[out] flags Pointer to the structure with flags of operation
 * @return Status of reading data:
 *                INPUT ERROR if data was entered incorrectly;
 *                NO_ERRORS if data was entered correctly;
 */
int ArgParser(int argc, const char *argv[], flags_t *flags);

/**
 * @brief  Initiallize flags of operation
 * @param[out] flags Pointer to the structure with flags of operation
 */
void InitiallizeFlags(flags_t *flags);

/**
* @brief The pointer to the function that changes flags
*/
typedef enum Errors (*changeflag_t) (flags_t *flags, const char *argv);


/** @struct option_t
 * @brief Structure for commands definition
 * @var option_t::name
 * Member 'name' is a short name of the command
 * @var option_t::long_name
 * Member 'long_name' is a long name of the command
 * @var option_t::change
 * Member 'change' is a pointer to the function that changes flags
 * @var option_t::description
 * Member 'description' is a description of the command
 * @var option_t::has_arg
 * Member 'has_arg' is a flag to show whether or not command has arguments
 */
typedef struct{
    const char *name;
    const char *long_name;
    changeflag_t change;
    const char *description;
    bool has_arg;
} option_t;

#endif /* ARG_PARSER_H */
