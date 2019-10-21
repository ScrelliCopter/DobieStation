#include <QApplication>
#include <memory>
#include "emuwindow.hpp"

using namespace std;

int main(int argc, char** argv)
{
    QApplication::setOrganizationName("PSI");
    QApplication::setApplicationName("DobieStation");
    QApplication::setOrganizationDomain("https://github.com/PSI-Rockin/DobieStation");

    QApplication a(argc, argv);

    auto logger = std::unique_ptr<Log>(new Log);
    ds_log = logger.get();

    EmuWindow* window = new EmuWindow();

    if (window->init(argc, argv))
        return 1;

    a.exec();
    return 0;
}
