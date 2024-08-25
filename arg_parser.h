#ifndef ARG_PARSER
#define ARG_PARSER

#include <stdio.h>
#include <string.h>

#include "print_colors.h"
#include "define_consts.h"

int ArgParser(int *argc, const char *argv[], flags_t *flags);
void InitiallizeFlags(flags_t *flags);

typedef int (*changeflag_t) (flags_t *flags, int *argc, const char **argv[]);

typedef struct{
    const char *name;
    const char *long_name;
    changeflag_t change;
    const char description[MAXLINE];
    bool has_arg;
} option_t;


#endif /* ARG_PARSER_H */
