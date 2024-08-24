#ifndef ARG_PARCER
#define ARG_PARCER

#include <stdio.h>
#include <string.h>

#include "define_consts.h"

int ArgParser(int *argc, const char *argv[], flags_t *flags);

typedef int (*changeflag_t) (flags_t *flags, int *argc, const char *argv[]);

typedef struct{
    const char *name;
    const char description[MAXLINE];
    changeflag_t change;
} option_t;


#endif /* ARG_PARCER_H */
