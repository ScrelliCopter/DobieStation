#include "logger.hpp"

Logger* ds_log;

Logger::Logger()
{
    try
    {
        // This is the sink for writing to console.
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%n] %v");
        console_sink->set_level(spdlog::level::info);

        // This sink create a log file and dumps everything to it. Note that the level logged to it is separate.
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ds_log.txt", true);
        file_sink->set_pattern("[%H:%M:%S %z] [%n] %v");
        file_sink->set_level(spdlog::level::trace);

        // Combine them both here.
        auto main_sink = std::make_shared<spdlog::sinks::dist_sink_mt>();
        main_sink->add_sink(console_sink);
        main_sink->add_sink(file_sink);

        // And the main logger and everything cloned from it uses that sink.
        main = std::make_shared<spdlog::logger>("DS", main_sink);
        spdlog::register_logger(main);

        ee = spdlog::get("DS")->clone("EE");
        ee_timing = spdlog::get("DS")->clone("EE Timing");

        iop = spdlog::get("DS")->clone("IOP");
        iop_dma = spdlog::get("DS")->clone("IOP DMA");
        iop_timing = spdlog::get("DS")->clone("IOP Timing");

        cop = spdlog::get("DS")->clone("COP");
        fpu = spdlog::get("DS")->clone("FPU");

        ipu = spdlog::get("DS")->clone("IPU");
        cdvd = spdlog::get("DS")->clone("CDVD");
        pad = spdlog::get("DS")->clone("PAD");
        spu = spdlog::get("DS")->clone("SPU");
        gif = spdlog::get("DS")->clone("GIF");
        gs = spdlog::get("DS")->clone("GS");
        gs_r = spdlog::get("DS")->clone("GS_r");
        gs_t = spdlog::get("DS")->clone("GS_t");
        sio2 = spdlog::get("DS")->clone("SIO2");
        sif = spdlog::get("DS")->clone("SIF");
        vif = spdlog::get("DS")->clone("VIF");
        dmac = spdlog::get("DS")->clone("DMAC");

        vu = spdlog::get("DS")->clone("VU");
        vu0 = spdlog::get("DS")->clone("VU0");
        vu1 = spdlog::get("DS")->clone("VU1");
        vu_jit = spdlog::get("DS")->clone("VU JIT");
        vu_jit64 = spdlog::get("DS")->clone("VU JIT64");

        spdlog::set_default_logger(main);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}
