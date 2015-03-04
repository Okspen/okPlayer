#include "tracktimelabel.h"

TrackTimeLabel::TrackTimeLabel(QWidget *parent) :
    QLabel(parent),
    m_modeCounter(0),
    m_position(0),
    m_duration(0)
{
    BASS::Core *player = Player::instance()->audio();
    connect(player, SIGNAL(positionChanged(qint32,qint32)), this, SLOT(updateTime(qint32, qint32)));
}

void TrackTimeLabel::updateTime(qint32 position, qint32 duration)
{
    if (position < 0)
        position = 0;

    if (duration < 0)
        duration = 0;

    QTime positionTime = QTime(0,0).addSecs(position);
    QTime lengthTime = QTime(0,0).addSecs(duration);

    QString format;

    if (duration >= 3600 * 1000) // more than hour
        format = "h:mm:ss";
    else
        format = "mm:ss";

    switch(m_modeCounter % 3)
    {
    case 0:
        setText(positionTime.toString(format) + "/" + lengthTime.toString(format));
        break;
    case 1:
        setText(positionTime.toString(format));
        break;
    case 2:
        setText("-" + QTime(0,0).addSecs(duration - position).toString(format));
        break;
    }

    m_position = position;
    m_duration = duration;
}

void TrackTimeLabel::mousePressEvent(QMouseEvent *e)
{
    ++m_modeCounter;
    updateTime(m_position, m_duration);
    QLabel::mousePressEvent(e);
}
