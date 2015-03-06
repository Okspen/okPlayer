#ifndef FASTSLIDER_H
#define FASTSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QDebug>

class FastSlider : public QSlider
{
    Q_OBJECT
public:
    explicit FastSlider(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // FASTSLIDER_H
