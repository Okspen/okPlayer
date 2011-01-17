#include "okplaypausebutton.h"

okPlayPauseButton::okPlayPauseButton(QWidget *parent) :
    QToolButton(parent)
{
    play = new QState;
    play->assignProperty(this, "icon", QIcon(":/tango/images/icons/tango/media-playback-start.png"));
    play->setObjectName("play");

    pause = new QState;
    pause->assignProperty(this, "icon", QIcon(":/tango/images/icons/tango/media-playback-pause.png"));
    pause->setObjectName("pause");

    play->addTransition(this, SIGNAL(clicked()), pause);
    pause->addTransition(this, SIGNAL(clicked()), play);

    machine.addState(play);
    machine.addState(pause);
    machine.setInitialState(play);
    machine.start();
}

okPlayPauseButton::~okPlayPauseButton()
{
    delete play;
    delete pause;
}
