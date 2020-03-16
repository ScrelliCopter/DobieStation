#include "loggingwindow.hpp"

#include <core/logger.hpp>
#include <array>
#include <tuple>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "tickmarkslider.hpp"
#include <QLabel>
#include <QFrame>
#include <QPushButton>

using namespace logger;

void test_logger();


#define SPLITTER std::make_tuple(logger::NUM_CATEGORIES, QString())
const std::array<std::tuple<logger::Category, QString>, logger::NUM_CATEGORIES + 7> cat_names = {
    std::make_tuple(logger::CAT_MISC, "Misc"),
    SPLITTER,
    std::make_tuple(logger::CAT_EE,        "EE"),
    std::make_tuple(logger::CAT_EE_TIMING, "EE Timing"),
    SPLITTER,
    std::make_tuple(logger::CAT_COP0, "COP0"),
    std::make_tuple(logger::CAT_FPU,  "FPU"),
    std::make_tuple(logger::CAT_COP2, "COP2"),
    SPLITTER,
    std::make_tuple(logger::CAT_IOP,        "IOP"),
    std::make_tuple(logger::CAT_IOP_DMA,    "IOP DMA"),
    std::make_tuple(logger::CAT_IOP_TIMING, "IOP Timing"),
    SPLITTER,
    std::make_tuple(logger::CAT_CDVD, "CDVD"),
    std::make_tuple(logger::CAT_IPU,  "IPU"),
    std::make_tuple(logger::CAT_PAD,  "PAD"),
    std::make_tuple(logger::CAT_SPU,  "SPU"),
    std::make_tuple(logger::CAT_GIF,  "GIF"),
    SPLITTER,
    std::make_tuple(logger::CAT_GS,     "GS"),
    std::make_tuple(logger::CAT_GS_R,   "GS Registers"),
    std::make_tuple(logger::CAT_GS_T,   "GS Thread"),
    std::make_tuple(logger::CAT_GS_JIT, "GS JIT"),
    SPLITTER,
    std::make_tuple(logger::CAT_DMAC, "DMAC"),
    std::make_tuple(logger::CAT_SIO2, "SIO2"),
    std::make_tuple(logger::CAT_SIF,  "SIF"),
    std::make_tuple(logger::CAT_VIF,  "VIF"),
    SPLITTER,
    std::make_tuple(logger::CAT_VU,       "VU"),
    std::make_tuple(logger::CAT_VU0,      "VU0"),
    std::make_tuple(logger::CAT_VU1,      "VU1"),
    std::make_tuple(logger::CAT_VU_JIT,   "VU JIT"),
    std::make_tuple(logger::CAT_VU_JIT64, "VU JIT64")};

const std::array<std::tuple<logger::Level, QString>, logger::NUM_LEVELS> levels = {
    std::make_tuple(logger::OFF,      "Off"),
    std::make_tuple(logger::CRITICAL, "Critical"),
    std::make_tuple(logger::ERROR,    "Error"),
    std::make_tuple(logger::WARN,     "Warning"),
    std::make_tuple(logger::INFO,     "Info"),
    std::make_tuple(logger::DEBUG,    "Debug"),
    std::make_tuple(logger::TRACE,    "Trace")};


LoggingWindow::LoggingWindow(QWidget* parent) :
    QWidget(parent, Qt::Tool)
{
    auto scroll_view = new QScrollArea(this);
    auto scroll_widget = create_view(this);
    scroll_view->setWidget(scroll_widget);
    scroll_view->setWidgetResizable(true);
    layout.addWidget(scroll_view, 1);

    auto button_box = new QHBoxLayout;
    auto btn_test = new QPushButton("Test", this);
    auto btn_close = new QPushButton("Close", this);
    button_box->addWidget(btn_test);
    button_box->addWidget(btn_close);
    layout.addLayout(button_box);

    connect(btn_test, &QPushButton::pressed, test_logger);
    connect(btn_close, &QPushButton::pressed, this, &QWidget::close);

    setLayout(&layout);
}

QWidget* LoggingWindow::create_view(QWidget* parent)
{
    auto* tick_text_func = static_cast<TickmarkSlider::TickTextFunc>([](int i) -> const QString&
    {
        static const auto empty = QString();
        if (i < 0 || (unsigned)i >= levels.size())
            return empty;
        return std::get<1>(levels[(unsigned)i]);
    });

    auto widget = new QWidget(parent);
    auto layout = new QGridLayout(widget);
    bool first_after_split = true;
    for (size_t i = 0; i < cat_names.size(); ++i)
    {
        // Treat NUM_CATEGORIES as a splitter
        if (std::get<0>(cat_names[i]) == NUM_CATEGORIES)
        {
            auto splitter = new QFrame(widget);
            splitter->setFrameShape(QFrame::HLine);
            splitter->setFrameShadow(QFrame::Sunken);
            layout->addWidget(splitter, (int)i, 0, 1, 2);
            first_after_split = true;
            continue;
        }

        auto label = new QLabel(std::get<1>(cat_names[i]), widget);
        QSlider* slider;
        if (first_after_split)
        {
            auto tm_slider = new TickmarkSlider(Qt::Horizontal, widget);
            tm_slider->setTickTextFunc(tick_text_func);

            slider = tm_slider;
            first_after_split = false;
        }
        else
        {
            slider = new QSlider(Qt::Horizontal, widget);
        }

        slider->setRange(0, levels.size() - 1);
        slider->setSingleStep(1);
        slider->setTickInterval(1);
        slider->setTickPosition(QSlider::TicksAbove);

        layout->addWidget(label, (int)i, 0, Qt::AlignBottom);
        layout->addWidget(slider, (int)i, 1, 1, 1);
    }
    layout->setColumnStretch(0, 0);
    layout->setRowStretch(0, 0);
    return widget;
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

    const char* cat_enum_text[] = {"CAT_MISC", "CAT_EE", "CAT_EE_TIMING", "CAT_IOP", "CAT_IOP_DMA", "CAT_IOP_TIMING", "CAT_COP0", "CAT_COP2", "CAT_FPU", "CAT_IPU", "CAT_CDVD", "CAT_PAD", "CAT_SPU", "CAT_GIF", "CAT_GS", "CAT_GS_R", "CAT_GS_T", "CAT_GS_JIT", "CAT_DMAC", "CAT_SIO2", "CAT_VIF", "CAT_SIF", "CAT_VU", "CAT_VU0", "CAT_VU1", "CAT_VU_JIT", "CAT_VU_JIT64"};
    for (int i = 0; i < NUM_CATEGORIES; ++i)
    {
        struct timespec wait = {0, 100000000};
        nanosleep(&wait, &wait);
        info(static_cast<Category>(i), "using category ");
        warn(static_cast<Category>(i), cat_enum_text[i]);
        if (i == NUM_CATEGORIES - 1)
            info_l(static_cast<Category>(i), "");
    }
}
