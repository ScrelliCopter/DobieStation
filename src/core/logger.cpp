#include "logger.hpp"
#include <cstdio>

using namespace logger;


void logger::log_write(Category cat, Level lvl, char eol, const char* fmt, va_list args)
{
    vfprintf(stderr, fmt, args);

    if (eol)
        putc(eol, stderr);
}
