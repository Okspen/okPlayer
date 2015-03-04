#ifndef OKSEEKSLIDER_H
#define OKSEEKSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QTime>
#include <QToolTip>
#include <cmath>
#include "widgets/fastslider.h"
#include "player/player.h"

class SeekSlider : public FastSlider
{
	Q_OBJECT
public:
    explicit SeekSlider(QWidget* parent);

public slots:
    void updatePosition(qint32 position, qint32 length);

protected:
    //void mouseReleaseEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *e);

signals:
    void positionChanged(qreal);

private:
    bool m_receivePosition;

    /* Last received position and length */
    qint32 m_position;
    qint32 m_length;

private slots:
    void receivePositionOn();
    void receivePositionOff();
    void translateValue(int value);
};

#endif // OKSEEKSLIDER_H
