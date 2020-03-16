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
        CAT_COP0,
        CAT_COP2,
        CAT_FPU,
        CAT_IPU,
        CAT_CDVD,
        CAT_PAD,
        CAT_SPU,
        CAT_GIF,
        CAT_GS,
        CAT_GS_R,
        CAT_GS_T,
        CAT_GS_JIT,
        CAT_DMAC,
        CAT_SIO2,
        CAT_SIF,
        CAT_VIF,
        CAT_VU,
        CAT_VU0,
        CAT_VU1,
        CAT_VU_JIT,
        CAT_VU_JIT64,

        NUM_CATEGORIES
    };

    enum Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF,

        NUM_LEVELS
    };

    void log_write(Category cat, Level lvl, const char* str, char eol = '\0');

    template <typename... Args>
    inline void log_write(Category cat, Level lvl, char eof, const char* fmt, const Args&... args)
    {
        try
        {
            log_write(cat, lvl, fmt::format(fmt, args...).c_str(), eof);
        }
        catch (std::exception& e)
        {
            fmt::print(stderr, "!!!! LOGGING ERROR: {} !!!!\n", e.what());
        }
    }

#define LOGGER_GENERATE_WRAPPER_FUNC(NAME, LVL) \
    inline void NAME(Category cat, const char* str) { \
        log_write(cat, LVL, str); } \
    inline void NAME##_l(Category cat, const char* str) { \
        log_write(cat, LVL, str, '\n'); } \
    template <typename... Args> \
    inline void NAME(Category cat, const char* fmt, const Args&... args) { \
        log_write(cat, LVL, '\0', fmt, args...); } \
    template <typename... Args> \
    inline void NAME##_l(Category cat, const char* fmt, const Args&... args) { \
        log_write(cat, LVL, '\n', fmt, args...); } \
    inline void NAME##_l(Category cat) { \
        log_write(cat, LVL, '\n', nullptr); }

    LOGGER_GENERATE_WRAPPER_FUNC(trace, TRACE)
    LOGGER_GENERATE_WRAPPER_FUNC(debug, DEBUG)
    LOGGER_GENERATE_WRAPPER_FUNC(info, INFO)
    LOGGER_GENERATE_WRAPPER_FUNC(warn, WARN)
    LOGGER_GENERATE_WRAPPER_FUNC(error, ERROR)
    LOGGER_GENERATE_WRAPPER_FUNC(critical, CRITICAL)

}

#endif//__LOGGER_HPP__