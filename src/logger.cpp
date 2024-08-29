#include "logger.h"

static logger_t* GetLogger() {
    static logger_t logger = {};
    return &logger;
}

void LoggerSetFile(FILE* out) {
    assert(out != nullptr);

    GetLogger()->file_out = out;
}

void LoggerSetLevel(enum LOG_LEVEL level) {
    GetLogger()->min_level = level;
}

void Log(enum LOG_LEVEL status, const char *fmt, ...) {
    assert(fmt != nullptr);

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
    vfprintf (GetLogger()->file_out, dst, args);
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
    return "!ERROR!";
}

void TimePrint(FILE *out) {
    assert(out != nullptr);

    time_t mytime = time(NULL);
    struct tm *time = localtime(&mytime);
    fprintf(out, "%02d.%02d.%d %02d:%02d:%02d ",
            time->tm_mday, time->tm_mon + 1, time->tm_year + 1900,
            time->tm_hour, time->tm_min,     time->tm_sec);
}

void AestheticizeString(const char *src, char *dst, size_t max_len) {
    assert(src != nullptr);
    assert(dst != nullptr);

    size_t len = strnlen(src, max_len);

    if (len == 0) {
        return;
    }
    size_t j = 0, i = 0;
    dst[j++] = '\n';
    dst[j++] = '\t';
    for(; i < len && j < max_len - 1; i++) {
        if (src[i] == '\n') {
            dst[j++] = '\n';
            dst[j++] = '\t';
        }
        else {
            dst[j++] = src[i];
        }
    }
    if (src[--i] == '\n') {
        dst[--j] = '\0';
    }
    else {
        dst[j] = '\0';
    }
}
