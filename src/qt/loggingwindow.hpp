#ifndef LOGGINGWINDOW_HPP
#define LOGGINGWINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>

class LoggingWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout layout;

    static QWidget* create_view(QWidget* parent = nullptr);

public:
    explicit LoggingWindow(QWidget* parent = nullptr);

};

#endif//LOGGINGWINDOW_HPP
