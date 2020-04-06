#include "loggingwindow.hpp"

#include "core/logger.hpp"
#include <array>
#include <tuple>
#include <thread>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

void test_logger();
void test_logger2();


#define SPLITTER std::make_tuple(logger::Category::NUM_CATEGORIES, QString())
const std::array<std::tuple<logger::Category, QString>, (int)logger::Category::NUM_CATEGORIES + 6> cat_names = {
    std::make_tuple(logger::Category::MISC, "Misc"),
    //SPLITTER,
    std::make_tuple(logger::Category::EE,        "EE"),
    std::make_tuple(logger::Category::EE_TIMING, "EE Timing"),
    SPLITTER,
    std::make_tuple(logger::Category::COP0, "COP0"),
    std::make_tuple(logger::Category::FPU,  "FPU"),
    std::make_tuple(logger::Category::COP2, "COP2"),
    SPLITTER,
    std::make_tuple(logger::Category::IOP,        "IOP"),
    std::make_tuple(logger::Category::IOP_DMA,    "IOP DMA"),
    std::make_tuple(logger::Category::IOP_TIMING, "IOP Timing"),
    SPLITTER,
    std::make_tuple(logger::Category::CDVD, "CDVD"),
    std::make_tuple(logger::Category::IPU,  "IPU"),
    std::make_tuple(logger::Category::PAD,  "PAD"),
    std::make_tuple(logger::Category::SPU,  "SPU"),
    std::make_tuple(logger::Category::GIF,  "GIF"),
    SPLITTER,
    std::make_tuple(logger::Category::GS,     "GS"),
    std::make_tuple(logger::Category::GS_R,   "GS Registers"),
    std::make_tuple(logger::Category::GS_T,   "GS Thread"),
    std::make_tuple(logger::Category::GS_JIT, "GS JIT"),
    SPLITTER,
    std::make_tuple(logger::Category::DMAC, "DMAC"),
    std::make_tuple(logger::Category::SIO2, "SIO2"),
    std::make_tuple(logger::Category::SIF,  "SIF"),
    std::make_tuple(logger::Category::VIF,  "VIF"),
    SPLITTER,
    std::make_tuple(logger::Category::VU,       "VU"),
    std::make_tuple(logger::Category::VU0,      "VU0"),
    std::make_tuple(logger::Category::VU1,      "VU1"),
    std::make_tuple(logger::Category::VU_JIT,   "VU JIT"),
    std::make_tuple(logger::Category::VU_JIT64, "VU JIT64")};

const std::array<std::tuple<logger::Level, QString>, (int)logger::Level::NUM_LEVELS> levels = {
    std::make_tuple(logger::Level::OFF,   "Off"),
    std::make_tuple(logger::Level::FATAL, "Fatal"),
    std::make_tuple(logger::Level::WARN,  "Warning"),
    std::make_tuple(logger::Level::INFO,  "Info"),
    std::make_tuple(logger::Level::DEBUG, "Debug"),
    std::make_tuple(logger::Level::TRACE, "Trace")};


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

    connect(btn_test, &QPushButton::pressed, []()
    {
        auto t = std::thread(test_logger);
        t.detach();
    });
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
        if (std::get<0>(category) == logger::Category::NUM_CATEGORIES)
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
    logger::writeline(logger::Category::MISC, logger::Level::INFO, "test {0}:{1:04X} {0}", "test", 10);
    logger::writeline(logger::Category::MISC, logger::Level::INFO, "poop {:i}", "oops"); // type error
    const char text[24] = {'N', 'G', 'A', 'G', 'L', 'E', 'R', 'I', 'D', 'Y', 'M', 'O', 'T', 'H', 'F', 'U', 'C', 'K'};
    logger::writeline(logger::Category::MISC, logger::Level::FATAL, "{}{}{} {}{}{} {}{} {}{}",
        fmt::basic_string_view<char>(text + 5, 1), fmt::basic_string_view<char>(text + 0, 4),
        fmt::basic_string_view<char>(text + 5, 1),
        fmt::basic_string_view<char>(text + 6, 3), fmt::basic_string_view<char>(text + 4, 2),
        fmt::basic_string_view<char>(text + 9, 1),
        fmt::basic_string_view<char>(text + 10, 4), fmt::basic_string_view<char>(text + 5, 2),
        fmt::basic_string_view<char>(text + 14, 4), fmt::basic_string_view<char>(text + 5, 2));

    test_logger2();

    const char* cat_enum_text[] = {"MISC", "EE", "EE_TIMING", "IOP", "IOP_DMA", "IOP_TIMING", "COP0", "COP2", "FPU",
        "IPU", "CDVD", "PAD", "SPU", "GIF", "GS", "GS_R", "GS_T", "GS_JIT", "DMAC", "SIO2", "VIF", "SIF", "VU", "VU0",
        "VU1", "VU_JIT", "VU_JIT64"};
    const char* lvl_enum_text[] = {"TRACE", "DEBUG", "INFO", "WARN", "FATAL", "OFF"};
    for (int i = 0; i < (int)logger::Category::NUM_CATEGORIES; ++i)
    {
        for (int j = 0; j < (int)logger::Level::NUM_LEVELS; ++j)
        {
            struct timespec wait = {0, 10000000};
            nanosleep(&wait, &wait);
            logger::writeline(static_cast<logger::Category>(i), static_cast<logger::Level>(j),
                "using category {} at severity level {}", cat_enum_text[i], lvl_enum_text[j]);
        }
    }
}

LOGGER_CREATE_CONVENIENCE_WRAPPERS(logger::Category::MISC)

void test_logger2()
{
    trace("trace");
    debug("debug");
    info("info");
    warn("warn");
    fatal("fatal");
}
