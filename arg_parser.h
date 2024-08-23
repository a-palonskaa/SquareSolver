#ifndef ARG_PARCER
#define ARG_PARCER

#include <stdio.h>
#include <string.h>

#include "define_consts.h"


void ArgParser(int argc, const char *argv[],
               enum FLAGS *flag_mode, enum OUTPUT_FLAGS *flag_output, enum INPUT_FLAGS  *flag_input,
               char *file_input, char *file_output);

#endif /* ARG_PARCER_H */
