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
    trace_l(CAT_MISC, "hi.");

    QApplication a(argc, argv);
    auto window = unique_ptr<EmuWindow>(new EmuWindow());

    if (window->init(argc, argv))
        return 1;

    a.exec();
    return 0;
}
