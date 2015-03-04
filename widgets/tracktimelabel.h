#ifndef TRACKTIMELABEL_H
#define TRACKTIMELABEL_H

#include <QLabel>
#include <QTime>
#include <cmath>
#include <QDebug>
#include <QTimer>
#include "player/player.h"

class TrackTimeLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TrackTimeLabel(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);

private slots:
    void updateTime(qint32 position, qint32 duration);

private:
    int m_modeCounter;
    qint32 m_position;
    qint32 m_duration;

    QTimer m_timer;
};

#endif // TRACKTIMELABEL_H
