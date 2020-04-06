#include <QApplication>
#include <memory>
#include "emuwindow.hpp"
#include "core/logger.hpp"


int main(int argc, char** argv)
{
    logger::add_sink(std::make_unique<logger::ConsoleSink>());
    logger::add_sink(std::make_unique<logger::FileSink>("filehandler_test.log"));

    QApplication::setOrganizationName("PSI");
    QApplication::setApplicationName("DobieStation");
    QApplication::setOrganizationDomain("https://github.com/PSI-Rockin/DobieStation");
    QApplication a(argc, argv);
    auto window = std::make_unique<EmuWindow>();

    if (window->init(argc, argv))
        return 1;

    QApplication::exec();
    return 0;
}
