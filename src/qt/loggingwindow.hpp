#ifndef LOGGINGWINDOW_HPP
#define LOGGINGWINDOW_HPP

#include <QWidget>
#include <QGridLayout>

class LoggingWindow : public QWidget
{
    Q_OBJECT
private:
    QGridLayout layout;

public:
    explicit LoggingWindow(QWidget* parent = nullptr);

};

#endif//LOGGINGWINDOW_HPP
