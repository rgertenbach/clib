// Requires LOG_LEVEL=LOG_ERROR (or some other level)
#ifndef LOG_H_
#define LOG_H_
#include <stdbool.h>
#include <stdio.h>

enum LogLevel {
    LOG_EVERYTHING = 0,
    LOG_DEBUG = 1,
    LOG_INFO = 2,
    LOG_WARN = 3,
    LOG_ERROR = 4,
    LOG_FATAL = 5,
    LOG_NOTHING = 6,
};

extern enum LogLevel LOG_LEVEL;

#ifndef LOG_STREAM
#define LOG_STREAM stderr
#endif  // LOG_STREAM

char *
format_log_level(enum LogLevel level)
{
    (void) fprintf;  // To silence warning of unused include.
    switch (level) {
    case LOG_DEBUG:
        return "[DEBUG]";
    case LOG_INFO:
        return "[INFO]";
    case LOG_WARN:
        return "[WARN]";
    case LOG_ERROR:
        return "[ERROR]";
    case LOG_FATAL:
        return "[FATAL]";
    default:
        return "[INVALID LOG LEVEL]";
    }
}

#define LOG(severity, fstring, ...)                                           \
    do {                                                                      \
        if (severity >= LOG_LEVEL) {                                          \
            fprintf(                                                          \
                LOG_STREAM, "%s %s:%d - " fstring,                            \
                format_log_level(severity), __FILE__,                         \
                __LINE__ __VA_OPT__(, __VA_ARGS__)                            \
            );                                                                \
        }                                                                     \
    } while (0)

#endif  // LOG_H_
