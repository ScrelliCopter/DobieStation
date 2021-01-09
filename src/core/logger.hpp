#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fmt/core.h>
#include <chrono>
#include <memory>

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

    enum class Level
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        FATAL,
        OFF,

        NUM_LEVELS
    };

    class LogSink
    {
    public:
        virtual ~LogSink() = default;
        virtual void write(Category cat, Level lvl, const std::chrono::system_clock::time_point& time, const char* str) = 0;
    };

    class ConsoleSink : public LogSink
    {
    public:
        void write(Category cat, Level lvl, const std::chrono::system_clock::time_point& time, const char* str) override;
    };

    class FileSink : public LogSink
    {
        FILE* stream;

    public:
        explicit FileSink(const char* path);
        ~FileSink() override;
        void write(Category cat, Level lvl, const std::chrono::system_clock::time_point& time, const char* str) override;
    };

    void add_sink(std::unique_ptr<LogSink>&& new_sink);

    void _write_internal(Category cat, Level lvl, const char* str);

    template <typename... Args>
    inline void _write_internal(Category cat, Level lvl, const char* fmt, const Args&... args)
    {
        try
        {
            _write_internal(cat, lvl, fmt::format(fmt, args...).c_str());
        }
        catch (std::exception& e)
        {
            fmt::print(stderr, "!!!! LOGGING ERROR: {} !!!!\n", e.what());
        }
    }

    inline void writeline(Category cat, Level lvl, const char* str)
    {
        _write_internal(cat, lvl, str);
    }

    template <typename... Args>
    inline void writeline(Category cat, Level lvl, const char* fmt, const Args&... args)
    {
        _write_internal(cat, lvl, fmt, args...);
    }
}

#define LOGGER_GENERATE_WRAPPER_FUNC(NAME, CAT, LVL) \
    inline void NAME(const char* str) { \
        logger::writeline(CAT, LVL, str); } \
    template <typename... Args> \
    inline void NAME(const char* fmt, const Args&... args) { \
        logger::writeline(CAT, LVL, fmt, args...); }

#define LOGGER_CREATE_CONVENIENCE_WRAPPERS(CAT) \
    LOGGER_GENERATE_WRAPPER_FUNC(trace, CAT, logger::Level::TRACE) \
    LOGGER_GENERATE_WRAPPER_FUNC(debug, CAT, logger::Level::DEBUG) \
    LOGGER_GENERATE_WRAPPER_FUNC(info, CAT, logger::Level::INFO) \
    LOGGER_GENERATE_WRAPPER_FUNC(warn, CAT, logger::Level::WARN) \
    LOGGER_GENERATE_WRAPPER_FUNC(fatal, CAT, logger::Level::FATAL)

#endif//LOGGER_HPP
