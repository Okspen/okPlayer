#ifndef OKTRACKTIMELABEL_H
#define OKTRACKTIMELABEL_H

#include <QLabel>
#include <QTime>
#include <cmath>
#include <okvlcwrapper.h>

class okTrackTimeLabel : public QLabel
{
    Q_OBJECT
public:
    explicit okTrackTimeLabel(QWidget *parent = 0);
    void setVLC(okVLCWrapper* newVLC);

protected:
	void mousePressEvent(QMouseEvent *e);

signals:

private slots:
    void updateTime();

private:
    okVLCWrapper* vlc;
    int modeCounter;
};

#endif // OKTRACKTIMELABEL_H
