#include "logger.h"

static logger_t* GetLogger()
{
    static logger_t logger = {};
    return &logger;
}

void LoggerSetFile(FILE* out) {
    GetLogger()->file_out = out;
}

void LoggerSetLevel(enum LOG_LEVEL level) {
    GetLogger()->min_level = level;
}

void Log(enum LOG_LEVEL status, const char *fmt, ...) {
    if (GetLogger()->min_level > status) {
        return;
    }

    char dst[MAXLINE] = "";
    AestheticizeString(fmt, dst, MAXLINE);

    va_list args = {};
    va_start (args, fmt);

    bool color = GetLogger()->file_out == stdout;
    fprintf(GetLogger()->file_out, "%s", LogMessageTypePrint (status, color));
    TimePrint(GetLogger()->file_out);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
    vfprintf (GetLogger()->file_out,dst, args);
#pragma clang diagnostic pop

    va_end (args);
}

const char* LogMessageTypePrint (enum LOG_LEVEL level, bool color) {
    if (color) {
        switch (level) {
        case ERROR:
            return RED("[ERROR] ");
        case WARNING:
            return YELLOW("[WARNING] ");
        case INFO:
            return BLUE("[INFO] ");
        case DEBUG:
            return GREEN("[DEBUG] ");
        default:
            break;
        }
    }
    else {
        switch (level) {
            case ERROR:
                return "[ERROR] ";
            case WARNING:
                return "[WARNING] ";
            case INFO:
                return "[INFO] ";
            case DEBUG:
                return "[DEBUG] ";
            default:
                break;
        }
    }
    return "!ERROR! ";
}
