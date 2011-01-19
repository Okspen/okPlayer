#ifndef OKPLAYPAUSEBUTTON_H
#define OKPLAYPAUSEBUTTON_H

#include <QToolButton>
#include <QStateMachine>
#include "okvlcwrapper.h"

class okPlayPauseButton : public QToolButton
{
    Q_OBJECT
public:
    explicit okPlayPauseButton(QWidget *parent = 0);
    ~okPlayPauseButton();
    void setExternalTransitions(okVLCWrapper *vlc);

signals:

public slots:

private:
    QState* play;
    QState* pause;
    QStateMachine machine;

};

#endif // OKPLAYPAUSEBUTTON_H
