#include "logger.hpp"
#include <cstdio>

using namespace logger;


void logger::log_write(Category cat, Level lvl, const std::string& str, char eol)
{
    fputs(str.c_str(), stderr);
    if (eol)
        putc(eol, stderr);
}
