#ifndef TICKMARKSLIDER_HPP
#define TICKMARKSLIDER_HPP

#include <QSlider>

class TickmarkSlider : public QSlider
{
    Q_OBJECT

public:
    explicit TickmarkSlider(QWidget* parent = nullptr) : QSlider(parent) {}
    explicit TickmarkSlider(Qt::Orientation orientation, QWidget* parent = nullptr) : QSlider(orientation, parent) {}
    void paintEvent(QPaintEvent* e) override;

    typedef const QString& (*TickTextFunc)(int i);
    void setTickTextFunc(TickTextFunc func) { tick_text_func = func; }

private:
    TickTextFunc tick_text_func = nullptr;
    int slider_width = 0;
};

#endif//TICKMARKSLIDER_HPP
