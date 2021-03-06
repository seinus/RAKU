#include <RAKU/core/log.h>

#include <time.h>
#include <stdarg.h>
#include <stdio.h>

#define TIME_BUFFER_SIZE 25
#define TIME_FORMAT "%a %d %b %Y %H:%M:%S"

#if defined(RAKU_DEBUG)
    #define LOG_FORMAT "[%s] %-6s | "
#else
    #define LOG_FORMAT "[%s] %-5s | "
#endif

static const char *log_levels[] = {
    "INFO",
    "TRACE",
    "WARN",
    "ERROR",
    "FATAL"
};

static void get_time(char *buffer, int max_size, const char *format)
{
    time_t t = time(NULL);
    strftime(buffer, max_size, format, localtime(&t));
}

RAKU_API
void raku_log(enum log_level level, const char *format, ...)
{
    char time[TIME_BUFFER_SIZE];
    get_time(time, TIME_BUFFER_SIZE, TIME_FORMAT);
    printf(LOG_FORMAT, time, log_levels[level]);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    fputc('\n', stdout);
}