#include <QApplication>
#include <memory>
#include "emuwindow.hpp"
#include <logger.hpp>

using namespace std;
using namespace logger;


int main(int argc, char** argv)
{
    QApplication::setOrganizationName("PSI");
    QApplication::setApplicationName("DobieStation");
    QApplication::setOrganizationDomain("https://github.com/PSI-Rockin/DobieStation");

    info_l(CAT_MISC, "test {0}:{1:04X} {0}", "test", 10);
    error(CAT_MISC, "poop {:i}", "oops"); // type error
    warn(CAT_MISC, "hi?");
    warn(CAT_MISC, "hi!");
    trace_l(CAT_EE, "hi.");

    trace_l(CAT_MISC, "trace");
    debug_l(CAT_MISC, "debug");
    info_l(CAT_MISC, "info");
    warn_l(CAT_MISC, "warn");
    error_l(CAT_MISC, "error");
    critical_l(CAT_MISC, "critical");

    info(CAT_MISC,       "CAT_MISC");
    info(CAT_EE,         "CAT_EE");
    info(CAT_EE_TIMING,  "CAT_EE_TIMING");
    info(CAT_IOP,        "CAT_IOP");
    info(CAT_IOP_DMA,    "CAT_IOP_DMA");
    info(CAT_IOP_TIMING, "CAT_IOP_TIMING");
    info(CAT_COP0,       "CAT_COP0");
    info(CAT_COP2,       "CAT_COP2");
    info(CAT_FPU,        "CAT_FPU");
    info(CAT_IPU,        "CAT_IPU");
    info(CAT_CDVD,       "CAT_CDVD");
    info(CAT_PAD,        "CAT_PAD");
    info(CAT_SPU,        "CAT_SPU");
    info(CAT_GIF,        "CAT_GIF");
    info(CAT_GS,         "CAT_GS");
    info(CAT_GS_R,       "CAT_GS_R");
    info(CAT_GS_T,       "CAT_GS_T");
    info(CAT_GS_JIT,     "CAT_GS_JIT");
    info(CAT_DMAC,       "CAT_DMAC");
    info(CAT_SIO2,       "CAT_SIO2");
    info(CAT_VIF,        "CAT_VIF");
    info(CAT_SIF,        "CAT_SIF");
    info(CAT_VU,         "CAT_VU");
    info(CAT_VU0,        "CAT_VU0");
    info(CAT_VU1,        "CAT_VU1");
    info(CAT_VU_JIT,     "CAT_VU_JIT");
    info_l(CAT_VU_JIT64,   "CAT_VU_JIT64");

    QApplication a(argc, argv);
    auto window = unique_ptr<EmuWindow>(new EmuWindow());

    if (window->init(argc, argv))
        return 1;

    a.exec();
    return 0;
}
