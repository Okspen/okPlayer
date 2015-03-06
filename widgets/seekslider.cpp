#include "seekslider.h"

SeekSlider::SeekSlider(QWidget* parent)
    : FastSlider(parent)
{
    setMinimum(0);
    setMaximum(100);
    setValue(0);
    setTickInterval(10);
    m_receivePosition = true;

    setMouseTracking(true);

    connect(this, SIGNAL(sliderPressed()), this, SLOT(receivePositionOff()));
    connect(this, SIGNAL(sliderReleased()), this, SLOT(receivePositionOn()));
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(translateValue(int)));

    BASS::Core *audio = Player::instance()->audio();
    connect(audio,  SIGNAL(positionChanged(qint32,qint32)), this,   SLOT(updatePosition(qint32,qint32)));
    connect(this,   SIGNAL(positionChanged(qreal)),         audio,  SLOT(setPosition(qreal)));
}

void SeekSlider::updatePosition(qint32 position, qint32 length)
{
    if (m_receivePosition == false)
        return;

    m_position = position;
    m_length = length;

    blockSignals(true);
    setValue(maximum() * (double) position / (double) length);
    blockSignals(false);

    setToolTip(BASS::Core::timeToString(position, length)
               + " / "
               + BASS::Core::timeToString(length, length));
}

void SeekSlider::receivePositionOn()
{
    m_receivePosition = true;
}

void SeekSlider::receivePositionOff()
{
    m_receivePosition = false;
}

void SeekSlider::translateValue(int value)
{
    qreal pos = (double) value / (double) maximum();
    emit positionChanged(pos);
}
