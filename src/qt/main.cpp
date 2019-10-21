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

    infol(CAT_MISC, "test %s", "test");

    QApplication a(argc, argv);
    auto window = unique_ptr<EmuWindow>(new EmuWindow());

    if (window->init(argc, argv))
        return 1;

    a.exec();
    return 0;
}
