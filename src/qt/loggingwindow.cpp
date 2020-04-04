#include "loggingwindow.hpp"

#include <core/logger.hpp>
#include <array>
#include <tuple>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

using namespace logger;

void test_logger();


#define SPLITTER std::make_tuple(logger::NUM_CATEGORIES, QString())
const std::array<std::tuple<logger::Category, QString>, logger::NUM_CATEGORIES + 6> cat_names = {
    std::make_tuple(logger::CAT_MISC, "Misc"),
    //SPLITTER,
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
    auto gbox = new QGroupBox(tr("Log level settings"), this);
    auto gbox_layout = create_view(gbox);
    gbox->setLayout(gbox_layout);
    layout.addWidget(gbox);

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

QLayout* LoggingWindow::create_view(QWidget* parent)
{
    constexpr int num_columns = 3;

    auto layout = new QGridLayout(parent);
    int row = 0, column = 0;
    for (const auto& category : cat_names)
    {
        // Treat NUM_CATEGORIES as a splitter
        if (std::get<0>(category) == NUM_CATEGORIES)
        {
            auto splitter = new QFrame(parent);
            splitter->setFrameShape(QFrame::HLine);
            splitter->setFrameShadow(QFrame::Sunken);

            // Add splitter to new row
            if (column)
                ++row;
            layout->addWidget(splitter, row++, 0, 1, num_columns * 2);
            column = 0;
            continue;
        }

        auto label = new QLabel(std::get<1>(category), parent);
        label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        auto cbx = new QComboBox(parent);
        for (const auto& level : levels)
            cbx->addItem(std::get<1>(level));

        layout->addWidget(label, row, column * 2);
        layout->addWidget(cbx, row, column * 2 + 1);
        if (++column >= num_columns)
        {
            ++row;
            column = 0;
        }
    }

    // Stretch combo boxes & not labels
    for (int i = 0; i < num_columns; ++i)
    {
        layout->setColumnStretch(i * 2, 0);
        layout->setColumnStretch(i * 2 + 1, 1);
    }

    return layout;
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
