/**
 * @file logger.h
 * @brief Logger
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#include "test_library.h"
#include "define_consts.h"

/**
 * @brief enum for the logging level
 */
enum LogLevel {
    DEBUG   = 0,    ///< debug level
    INFO    = 1,    ///< informational level
    WARNING = 2,    ///< warning level
    ERROR   = 3     ///< error level
};

/** @struct logger_t
 * @brief Structure for the logger
 * @var logger_t::file_out
 * Member 'file_out' is a pointer to the file to print results
 * @var logger_t::min_level
 * Member 'min_level' is a minimum logger level
 */
typedef struct {
    FILE* file_out;
    enum LogLevel min_level;
} logger_t;

/**
 * @brief  Change mode of operation to the test mode
 * @param[in] status Logging status
 * @param[in]  ...   Arguments for format specification
 */
void Log(enum LogLevel status, const char *fmt, ...);

/**
 * @brief  Set output file
 * @param[in] out Pointer to the file to print results
 */
void LoggerSetFile(FILE* out);

/**
 * @brief  Set output file
 * @param[in] level Logging level
 */
void LoggerSetLevel(enum LogLevel level);

/**
 * @brief  Identify the message type
 * @param[in] level Logging level
 * @param[in] color Bool to define where or not dye status
 */
const char* LogMessageTypePrint(enum LogLevel level, bool color);

/**
* @brief Print the time of the message
* @param[in] out Pointer to the output file
*/
void TimePrint(FILE *out);

/**
* @brief Add tabs for each line
* @param[in] out Pointer to the output file
*/
void AestheticizeString(const char *src, char *dst, size_t max_len);

#endif /* LOGGER_H */
