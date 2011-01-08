#ifndef OKSEEKSLIDER_H
#define OKSEEKSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <cmath>
#include <okvlcwrapper.h>

class okSeekSlider : public QSlider
{
	Q_OBJECT
public:
    okSeekSlider(QWidget* parent);
    void setVLC(okVLCWrapper* newVLC);

public slots:
    void updatePosition();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    okVLCWrapper* vlc;
};

#endif // OKSEEKSLIDER_H
