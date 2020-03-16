#include "logger.hpp"
#include <cstdio>
#include <chrono>
#include <fmt/chrono.h>

using namespace logger;
namespace chrono { using namespace std::chrono; }

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
    switch (lvl)
    {
    case (TRACE):    return ESC(DIM);
    case (DEBUG):    return ESC(FG_BLUE);
    //case (INFO):     return ESC(RESET);
    case (WARN):     return ESC(FG_YELLOW);
    case (ERROR):    return ESC(FG_RED);
    case (CRITICAL): return ESC2(BRIGHT, BG_RED);

    default: return "";
    }
}

constexpr const char* category_token(Category cat)
{
    switch (cat)
    {
    case (CAT_EE):         return "EE: ";
    case (CAT_EE_TIMING):  return "EE Timing: ";
    case (CAT_IOP):        return "IOP: ";
    case (CAT_IOP_DMA):    return "IOP DMA: ";
    case (CAT_IOP_TIMING): return "IOP Timing: ";
    case (CAT_COP0):       return "COP0: ";
    case (CAT_COP2):       return "COP2: ";
    case (CAT_FPU):        return "FPU: ";
    case (CAT_IPU):        return "IPU: ";
    case (CAT_CDVD):       return "CDVD: ";
    case (CAT_PAD):        return "PAD: ";
    case (CAT_SPU):        return "SPU: ";
    case (CAT_GIF):        return "GIF: ";
    case (CAT_GS):         return "GS: ";
    case (CAT_GS_R):       return "GS Registers: ";
    case (CAT_GS_T):       return "GS Thread: ";
    case (CAT_GS_JIT):     return "GS JIT: ";
    case (CAT_DMAC):       return "DMAC: ";
    case (CAT_SIO2):       return "SIO2: ";
    case (CAT_SIF):        return "SIF: ";
    case (CAT_VIF):        return "VIF: ";
    case (CAT_VU):         return "VU: ";
    case (CAT_VU0):        return "VU0: ";
    case (CAT_VU1):        return "VU1: ";
    case (CAT_VU_JIT):     return "VU_JIT: ";
    case (CAT_VU_JIT64):   return "VU_JIT64: ";

    default: return "";
    }
}


void write_date(FILE* f)
{
    auto now = chrono::high_resolution_clock::now();
    auto ltime = chrono::system_clock::to_time_t(now);
    auto frac_sec = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    fmt::print(stderr, "[{:%H:%M:%S}.{:03d}] ", *std::localtime(&ltime), frac_sec);
}

void logger::log_write(Category cat, Level lvl, const char* str, char eol)
{
    static Category last_cat = NUM_CATEGORIES;
    static char     last_eol = '\n';

    if (last_eol == '\n')
    {
        fputs(ESC(DIM), stderr);
        write_date(stderr);
        fputs(ESC(FG_GREEN), stderr);
        fputs(category_token(cat), stderr);
    }
    else if (cat != last_cat)
    {
        putc('\n', stderr);
        fputs(ESC(DIM), stderr);
        write_date(stderr);
        fputs(ESC(FG_GREEN), stderr);
        fputs(category_token(cat), stderr);
    }

    last_cat = cat;
    last_eol = eol;

    fputs(ESC(RESET), stderr);
    fputs(level_esc(lvl), stderr);
    if (str)
        fputs(str, stderr);
    fputs(ESC(RESET), stderr);
    if (eol)
        putc(eol, stderr);
}