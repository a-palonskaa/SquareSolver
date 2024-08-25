#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#include "test_library.h"
#include "define_consts.h"

typedef struct {
    FILE* file_out;
    enum LOG_LEVEL min_level;
} logger_t;


void Log(enum LOG_LEVEL status, const char *fmt, ...);
void LoggerSetFile(FILE* out);
void LoggerSetLevel(enum LOG_LEVEL level);
const char* LogPrint(enum LOG_LEVEL level, bool color);

#endif /* LOGGER_H */
