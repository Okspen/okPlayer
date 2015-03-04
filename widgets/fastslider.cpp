#include "fastslider.h"

FastSlider::FastSlider(QWidget *parent) :
    QSlider(parent)
{
}

void FastSlider::mousePressEvent(QMouseEvent *ev)
{
    //QSlider::mousePressEvent(ev);
    if (ev->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum() - minimum()) * (height() - ev->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum() - minimum()) * ev->x()) / width() ) ;

        ev->accept();
    }
    QSlider::mousePressEvent(ev);
}
