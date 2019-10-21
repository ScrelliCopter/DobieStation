#ifndef LOGGER_HPP
#define LOGGER_HPP

// Don't add endlines automatically.
#define SPDLOG_EOL ""

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/dist_sink.h"

class Logger
{
public:
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

    Logger();
    ~Logger() = default;
};

extern Logger* ds_log;

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
    CAT_VU_JIT64
};

template <typename... Args>
inline void info_l(Category cat, const char* fmt, Args&... args)
{
    ds_log->main->log(spdlog::level::level_enum::info, fmt, args...);
    ds_log->main->log(spdlog::level::level_enum::info, '\n');
}

#endif//LOGGER_HPP
