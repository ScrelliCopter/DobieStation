#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <fmt/core.h>

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

    void log_write(Category cat, Level lvl, const std::string& str, char eol = 0);


    inline void info(Category cat, const char* str) { log_write(cat, INFO, str); }

    inline void infol(Category cat, const char* str) { log_write(cat, INFO, str, '\n'); }

    template <typename... Args>
    inline void info(Category cat, const char* fmt, const Args&... args)
    {
        log_write(cat, INFO, fmt::format(fmt, args...));
    }

    template <typename... Args>
    inline void infol(Category cat, const char* fmt, const Args&... args)
    {
        log_write(cat, INFO, fmt::format(fmt, args...), '\n');
    }
}

#endif//__LOGGER_HPP__
