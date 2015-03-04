#ifndef PLAYPAUSEBUTTON_H
#define PLAYPAUSEBUTTON_H

#include <QToolButton>
#include <QStateMachine>
#include "player/player.h"

class PlayPauseButton : public QToolButton
{
    Q_OBJECT
public:
    explicit PlayPauseButton(QWidget *parent = 0);
    ~PlayPauseButton();
    void setPlayer(BASS::Core *player);

private:
    QState* play;
    QState* pause;
    QStateMachine machine;
    BASS::Core *m_player;

private slots:
    void processClick();

};

#endif // PLAYPAUSEBUTTON_H
