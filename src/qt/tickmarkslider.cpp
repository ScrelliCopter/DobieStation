#include "tickmarkslider.hpp"

#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionSlider>


void TickmarkSlider::paintEvent(QPaintEvent* e)
{
    if (!tick_text_func || orientation() == Qt::Vertical || tickPosition() == NoTicks)
    {
        QSlider::paintEvent(e);
        return;
    }

    QPainter p(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    // Calculate slider position and widget height
    QRect r1;
    p.drawText(r1, Qt::TextDontPrint, "Gidget", &r1);
    r1.setWidth(width());
    opt.rect.adjust(0, r1.height(), 0, 0);
    if (!slider_width)
        slider_width = height();
    setMinimumHeight(slider_width + r1.height());

    // Draw base slider
    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderHandle | QStyle::SC_SliderTickmarks;
    style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, this);

    // Get base slider geometry
    QStyleOptionSlider slider_style;
    slider_style.init(this);
    slider_style.orientation = orientation();
    int available = style()->pixelMetric(QStyle::PM_SliderSpaceAvailable, &slider_style, this);
    int offset = style()->pixelMetric(QStyle::PM_SliderLength, &slider_style, this) / 2;

    QRect r2, r3;
    for (int i = minimum(); i <= maximum(); i += tickInterval())
    {
        // Find value label position relative to slider
        int left = QStyle::sliderPositionFromValue(minimum(), maximum(), i, available) + offset;
        QPoint point(left, rect().top() + r1.height());

        r2.setTopLeft(point);
        //QString text = QString("%L1").arg(i);
        QString text = tick_text_func(i);
        p.drawText(r2, Qt::TextDontPrint, text, &r3);
        if (i >= maximum())
            point -= QPoint(r3.width(), 0);
        else if (i > minimum())
            point -= QPoint(r3.width() / 2, 0);
        p.drawText(point, text);
    }
}
