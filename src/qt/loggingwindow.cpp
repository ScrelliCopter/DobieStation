#include "loggingwindow.hpp"

#include <core/logger.hpp>
#include <array>
#include <tuple>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>

using namespace logger;

void test_logger();


static constexpr std::array<std::tuple<logger::Category, const char*>, logger::NUM_CATEGORIES> cat_names = {
    std::make_tuple(logger::CAT_MISC, "Misc"),

    std::make_tuple(logger::CAT_EE,        "EE"),
    std::make_tuple(logger::CAT_EE_TIMING, "EE Timing"),

    std::make_tuple(logger::CAT_IOP,        "IOP"),
    std::make_tuple(logger::CAT_IOP_DMA,    "IOP DMA"),
    std::make_tuple(logger::CAT_IOP_TIMING, "IOP Timing"),

    std::make_tuple(logger::CAT_CDVD, "CDVD"),
    std::make_tuple(logger::CAT_IPU,  "IPU"),
    std::make_tuple(logger::CAT_PAD,  "PAD"),
    std::make_tuple(logger::CAT_SPU,  "SPU"),
    std::make_tuple(logger::CAT_GIF,  "GIF"),

    std::make_tuple(logger::CAT_GS,   "GS"),
    std::make_tuple(logger::CAT_GS_R, "GS_r"),
    std::make_tuple(logger::CAT_GS_T, "GS_t"),

    std::make_tuple(logger::CAT_DMAC, "DMAC"),
    std::make_tuple(logger::CAT_SIO2, "SIO2"),
    std::make_tuple(logger::CAT_SIF,  "SIF"),
    std::make_tuple(logger::CAT_VIF,  "VIF"),

    std::make_tuple(logger::CAT_VU,       "VU"),
    std::make_tuple(logger::CAT_VU0,      "VU0"),
    std::make_tuple(logger::CAT_VU1,      "VU1"),
    std::make_tuple(logger::CAT_VU_JIT,   "VU JIT"),
    std::make_tuple(logger::CAT_VU_JIT64, "VU JIT64")};

static constexpr std::array<std::tuple<logger::Level, const char*>, logger::NUM_LEVELS> levels = {
    std::make_tuple(logger::TRACE,    "Trace"),
    std::make_tuple(logger::DEBUG,    "Debug"),
    std::make_tuple(logger::INFO,     "Info"),
    std::make_tuple(logger::WARN,     "Warning"),
    std::make_tuple(logger::ERROR,    "Error"),
    std::make_tuple(logger::CRITICAL, "Critical"),
    std::make_tuple(logger::OFF,      "Off")};


LoggingWindow::LoggingWindow(QWidget* parent) :
    QWidget(parent, Qt::Tool)
{
    for (size_t i = 0; i < levels.size(); ++i)
        layout.addWidget(new QLabel(std::get<1>(levels[i])), 0, (int)i + 1);

    for (size_t i = 0; i < logger::NUM_CATEGORIES; ++i)
    {
        auto label = new QLabel(std::get<1>(cat_names[i]), this);
        layout.addWidget(label, (int)i + 1, 0);

        auto btn_group = new QButtonGroup(this);
        for (size_t j = 0; j < levels.size(); ++j)
        {
            auto button = new QRadioButton(this);
            if (!j)
                button->setChecked(true);

            btn_group->addButton(button, (int)j);
            layout.addWidget(button, (int)i + 1, (int)j + 1);
        }
    }

    layout.setColumnStretch(0, 0);
    layout.setRowStretch(0, 0);
    setLayout(&layout);
}


void test_logger()
{
    info_l(CAT_MISC, "test {0}:{1:04X} {0}", "test", 10);
    error(CAT_MISC, "poop {:i}", "oops"); // type error
    const char text[24] = {'N', 'G', 'A', 'G', 'L', 'E', 'R', 'I', 'D', 'Y', 'M', 'O', 'T', 'H', 'F', 'U', 'C', 'K'};
    critical_l(CAT_MISC, "{}{}{} {}{}{} {}{} {}{}",
        fmt::basic_string_view<char>(text + 5, 1), fmt::basic_string_view<char>(text + 0, 4), fmt::basic_string_view<char>(text + 5, 1),
        fmt::basic_string_view<char>(text + 6, 3), fmt::basic_string_view<char>(text + 4, 2), fmt::basic_string_view<char>(text + 9, 1),
        fmt::basic_string_view<char>(text + 10, 4), fmt::basic_string_view<char>(text + 5, 2),
        fmt::basic_string_view<char>(text + 14, 4), fmt::basic_string_view<char>(text + 5, 2));
    info(CAT_MISC, "hi?");
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
        info(static_cast<Category>(i), "using category ");
        warn(static_cast<Category>(i), cat_names[i]);
        if (i == NUM_CATEGORIES - 1)
            info_l(static_cast<Category>(i), "");
    }
}
