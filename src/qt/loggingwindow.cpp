#include "loggingwindow.hpp"

#include <logger.hpp>
#include <array>
#include <tuple>
#include <QLabel>
#include <QSlider>


namespace logger { constexpr int NUM_LEVELS = logger::OFF + 1; }

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
        auto slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(0, logger::OFF);
        slider->setSingleStep(1);
        slider->setTickInterval(1);
        slider->setTickPosition(QSlider::TicksAbove);

        layout.addWidget(label, (int)i + 1, 0);
        layout.addWidget(slider, (int)i + 1, 1, 1, levels.size());
    }

    layout.setColumnStretch(0, 0);
    layout.setRowStretch(0, 0);
    setLayout(&layout);
}
