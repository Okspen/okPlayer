#include "oktracktimelabel.h"

okTrackTimeLabel::okTrackTimeLabel(QWidget *parent) :
    QLabel(parent)
{
    modeCounter = 0;
}

void okTrackTimeLabel::setVLC(okVLCWrapper *newVLC)
{
    if(newVLC == 0) return;
    vlc = newVLC;
    connect(vlc, SIGNAL(tick()), this, SLOT(updateTime()));
}

void okTrackTimeLabel::updateTime()
{
    int totalsec = vlc->getLength()/1000;
	int currentsec = ceil(vlc->getPosition() * totalsec);

    QString format;
    if(totalsec/3600 > 0) format = "h:mm:ss";
    else format = "mm:ss";

    switch(modeCounter % 3)
    {
    case 0:
        setText(QTime().addSecs(currentsec).toString(format) + "/" + QTime().addSecs(totalsec).toString(format));
        break;
    case 1:
        setText(QTime().addSecs(currentsec).toString(format));
        break;
    case 2:
        setText("-" + QTime().addSecs(totalsec-currentsec).toString(format));
        break;
    }

	if(totalsec/3600 > 0) setFixedWidth(fontMetrics().width("0:00:00/0:00:00"));
	else setFixedWidth(fontMetrics().width("00:00/00:00"));
}

void okTrackTimeLabel::mousePressEvent(QMouseEvent *e)
{
    modeCounter++;
}
