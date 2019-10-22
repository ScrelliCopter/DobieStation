#include "logger.hpp"
#include <cstdio>

using namespace logger;

#define EC_RESET      "0"
#define EC_BRIGHT     "1"
#define EC_DIM        "2"
#define EC_UNDERSCORE "4"
#define EC_BLINK      "5"
#define EC_REVERSE    "7"
#define EC_HIDDEN     "8"

#define EC_FG_BLACK   "30"
#define EC_FG_RED     "31"
#define EC_FG_GREEN   "32"
#define EC_FG_YELLOW  "33"
#define EC_FG_BLUE    "34"
#define EC_FG_MAGENTA "35"
#define EC_FG_CYAN    "36"
#define EC_FG_WHITE   "37"

#define EC_BG_BLACK   "40"
#define EC_BG_RED     "41"
#define EC_BG_GREEN   "42"
#define EC_BG_YELLOW  "43"
#define EC_BG_BLUE    "44"
#define EC_BG_MAGENTA "45"
#define EC_BG_CYAN    "46"
#define EC_BG_WHITE   "47"

#define ESC(CODE) ("\033[" EC_##CODE "m")
#define ESC2(CODE1, CODE2) ("\033[" EC_##CODE1 ";" EC_##CODE2 "m")

constexpr const char* level_esc(Level lvl)
{
    //TODO: switch in constexpr a c++14 extension
    switch (lvl)
    {
    case (TRACE):    return ESC(DIM);
    case (DEBUG):    return ESC(FG_BLUE);
    case (INFO):     return ESC(RESET);
    case (WARN):     return ESC(FG_GREEN);
    case (ERROR):    return ESC(FG_RED);
    case (CRITICAL): return ESC2(BRIGHT, BG_RED);

    default: return ESC(RESET);
    }
}


void logger::log_write(Category cat, Level lvl, const std::string& str, char eol)
{
    fputs(level_esc(lvl), stderr);
    fputs(str.c_str(), stderr);
    fputs(ESC(RESET), stderr);
    if (eol)
        putc(eol, stderr);
}
