#ifndef LOGGER_HPP
#define LOGGER_HPP

// Don't add endlines automatically.
#define SPDLOG_EOL ""

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/dist_sink.h"

class Log;
extern Log* ds_log;

class Log
{
public:
    enum class Category
    {
        MISC,
        EE,
        EE_TIMING,
        IOP,
        IOP_DMA,
        IOP_TIMING,
        COP,
        FPU,
        IPU,
        CDVD,
        PAD,
        SPU,
        GIF,
        GS,
        GS_R,
        GS_T,
        DMAC,
        SIO2,
        SIF,
        VIF,
        VU,
        VU0,
        VU1,
        VU_JIT,
        VU_JIT64
    };

    enum class Level
    {
        TRACE = SPDLOG_LEVEL_TRACE,
        DEBUG = SPDLOG_LEVEL_DEBUG,
        INFO = SPDLOG_LEVEL_INFO,
        WARN = SPDLOG_LEVEL_WARN,
        ERROR = SPDLOG_LEVEL_ERROR,
        CRITICAL = SPDLOG_LEVEL_CRITICAL,
        OFF = SPDLOG_LEVEL_OFF
    };

    template <typename... Args>
    static void write(Category cat, Level lvl, const char* fmt, Args&... args)
    {
        ds_log->main->log(static_cast<spdlog::level::level_enum>(lvl), fmt, args...);
    }

    std::shared_ptr<spdlog::logger> main;

    std::shared_ptr<spdlog::logger> ee;
    std::shared_ptr<spdlog::logger> ee_timing;

    std::shared_ptr<spdlog::logger> iop;
    std::shared_ptr<spdlog::logger> iop_dma;
    std::shared_ptr<spdlog::logger> iop_timing;

    std::shared_ptr<spdlog::logger> cop;
    std::shared_ptr<spdlog::logger> fpu;

    std::shared_ptr<spdlog::logger> ipu;
    std::shared_ptr<spdlog::logger> cdvd;
    std::shared_ptr<spdlog::logger> pad;
    std::shared_ptr<spdlog::logger> spu;
    std::shared_ptr<spdlog::logger> gif;
    std::shared_ptr<spdlog::logger> gs;
    std::shared_ptr<spdlog::logger> gs_r;
    std::shared_ptr<spdlog::logger> gs_t;
    std::shared_ptr<spdlog::logger> dmac;
    std::shared_ptr<spdlog::logger> sio2;
    std::shared_ptr<spdlog::logger> sif;
    std::shared_ptr<spdlog::logger> vif;

    std::shared_ptr<spdlog::logger> vu;
    std::shared_ptr<spdlog::logger> vu0;
    std::shared_ptr<spdlog::logger> vu1;
    std::shared_ptr<spdlog::logger> vu_jit;
    std::shared_ptr<spdlog::logger> vu_jit64;

    Log();
    ~Log() = default;
};

#endif//LOGGER_HPP
