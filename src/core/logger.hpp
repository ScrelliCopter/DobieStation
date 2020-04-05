#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <fmt/core.h>

namespace logger
{
    enum class Category
    {
        MISC,
        EE,
        EE_TIMING,
        IOP,
        IOP_DMA,
        IOP_TIMING,
        COP0,
        COP2,
        FPU,
        IPU,
        CDVD,
        PAD,
        SPU,
        GIF,
        GS,
        GS_R,
        GS_T,
        GS_JIT,
        DMAC,
        SIO2,
        SIF,
        VIF,
        VU,
        VU0,
        VU1,
        VU_JIT,
        VU_JIT64,

        NUM_CATEGORIES
    };

    enum Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        FATAL,
        OFF,

        NUM_LEVELS
    };

    void __write_internal(Category cat, Level lvl, const char* str, char eol);

    template <typename... Args>
    inline void __write_internal(Category cat, Level lvl, char eol, const char* fmt, const Args&... args)
    {
        try
        {
            __write_internal(cat, lvl, fmt::format(fmt, args...).c_str(), eol);
        }
        catch (std::exception& e)
        {
            fmt::print(stderr, "!!!! LOGGING ERROR: {} !!!!\n", e.what());
        }
    }

    inline void log_write(Category cat, Level lvl, const char* str)
    {
        __write_internal(cat, lvl, str, '\0');
    }

    inline void log_writeline(Category cat, Level lvl, const char* str)
    {
        __write_internal(cat, lvl, str, '\n');
    }

    template <typename... Args>
    inline void log_write(Category cat, Level lvl, const char* fmt, const Args&... args)
    {
        __write_internal(cat, lvl, '\0', fmt, args...);
    }

    template <typename... Args>
    inline void log_writeline(Category cat, Level lvl, const char* fmt, const Args&... args)
    {
        __write_internal(cat, lvl, '\n', fmt, args...);
    }
}

#define __LOGGER_GENERATE_WRAPPER_FUNC(NAME, CAT, LVL) \
    inline void NAME(const char* str) { \
        logger::log_write(CAT, LVL, str); } \
    inline void NAME##_l(const char* str) { \
        logger::log_writeline(CAT, LVL, str); } \
    template <typename... Args> \
    inline void NAME(const char* fmt, const Args&... args) { \
        logger::log_write(CAT, LVL, fmt, args...); } \
    template <typename... Args> \
    inline void NAME##_l(const char* fmt, const Args&... args) { \
        logger::log_writeline(CAT, LVL, fmt, args...); } \
    inline void NAME##_l() { \
        logger::log_writeline(CAT, LVL, nullptr); }

#define LOGGER_CREATE_CONVENIENCE_WRAPPERS(CAT) \
    __LOGGER_GENERATE_WRAPPER_FUNC(trace, CAT, logger::TRACE) \
    __LOGGER_GENERATE_WRAPPER_FUNC(debug, CAT, logger::DEBUG) \
    __LOGGER_GENERATE_WRAPPER_FUNC(info, CAT, logger::INFO) \
    __LOGGER_GENERATE_WRAPPER_FUNC(warn, CAT, logger::WARN) \
    __LOGGER_GENERATE_WRAPPER_FUNC(fatal, CAT, logger::FATAL)

#endif//__LOGGER_HPP__
