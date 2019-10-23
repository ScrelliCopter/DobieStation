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
    const char text[24] = {'E', 'N', 'G', 'A', 'G', 'E', 'R', 'I', 'D', 'L', 'E', 'Y', 'M', 'O', 'T', 'H', 'E', 'R', 'F', 'U', 'C', 'K', 'E', 'R'};
    critical_l(CAT_MISC, "{} {} {} {}",
        fmt::basic_string_view<char>(text +  0, 6),
        fmt::basic_string_view<char>(text +  6, 6),
        fmt::basic_string_view<char>(text + 12, 6),
        fmt::basic_string_view<char>(text + 18, 6));
    warn(CAT_MISC, "hi?");
    warn(CAT_MISC, "hi!");
    trace_l(CAT_EE, "hi.");

    trace_l(CAT_MISC, "trace");
    debug_l(CAT_MISC, "debug");
    info_l(CAT_MISC, "info");
    warn_l(CAT_MISC, "warn");
    error_l(CAT_MISC, "error");
    critical_l(CAT_MISC, "critical");

    const char* cat_names[] = {"CAT_MISC", "CAT_EE", "CAT_EE_TIMING", "CAT_IOP", "CAT_IOP_DMA", "CAT_IOP_TIMING", "CAT_COP0", "CAT_COP2", "CAT_FPU", "CAT_IPU", "CAT_CDVD", "CAT_PAD", "CAT_SPU", "CAT_GIF", "CAT_GS", "CAT_GS_R", "CAT_GS_T", "CAT_GS_JIT", "CAT_DMAC", "CAT_SIO2", "CAT_VIF", "CAT_SIF", "CAT_VU", "CAT_VU0", "CAT_VU1", "CAT_VU_JIT", "CAT_VU_JIT64"};
    for (int i = 0; i < NUM_CATEGORIES; ++i)
    {
        struct timespec wait = {0, 100000000};
        nanosleep(&wait, &wait);
        info_l(static_cast<Category>(i), cat_names[i]);
    }

    QApplication a(argc, argv);
    auto window = unique_ptr<EmuWindow>(new EmuWindow());

    if (window->init(argc, argv))
        return 1;

    a.exec();
    return 0;
}
