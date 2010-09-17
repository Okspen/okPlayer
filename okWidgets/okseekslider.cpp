#include "okseekslider.h"

okSeekSlider::okSeekSlider(QWidget* parent) : QSlider(parent)
{
}

void okSeekSlider::mousePressEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    setValue(maximum()*x/width());
    vlc->setPosition(value());
}

void okSeekSlider::mouseMoveEvent(QMouseEvent *ev)
{
    int x = ev->pos().x();
    setValue(maximum()*x/width());
    vlc->setPosition(value());
}

void okSeekSlider::setVLC(okVLCWrapper *newVLC)
{
	if(newVLC == 0) return;
	vlc = newVLC;
	connect(vlc, SIGNAL(tick()), this, SLOT(updatePosition()));
}

void okSeekSlider::updatePosition()
{
    if(isSliderDown()) return;
	setValue(vlc->getPosition()*1000);

	if(vlc->isEnded()) setValue(1000);
}
