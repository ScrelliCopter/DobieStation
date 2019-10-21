#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <cstdarg>

namespace logger
{
    enum Category
    {
        CAT_MISC,
        CAT_EE,
        CAT_EE_TIMING,
        CAT_IOP,
        CAT_IOP_DMA,
        CAT_IOP_TIMING,
        CAT_COP,
        CAT_FPU,
        CAT_IPU,
        CAT_CDVD,
        CAT_PAD,
        CAT_SPU,
        CAT_GIF,
        CAT_GS,
        CAT_GS_R,
        CAT_GS_T,
        CAT_DMAC,
        CAT_SIO2,
        CAT_SIF,
        CAT_VIF,
        CAT_VU,
        CAT_VU0,
        CAT_VU1,
        CAT_VU_JIT,
        CAT_VU_JIT64,

        CAT_LAST = CAT_VU_JIT64
    };

    enum Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF
    };

    void log_write(Category cat, Level lvl, char eol, const char* fmt, va_list args);

    inline void infol(Category cat, const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        log_write(cat, INFO, '\n', fmt, args);
        va_end(args);
    }
}

#endif//__LOGGER_HPP__
