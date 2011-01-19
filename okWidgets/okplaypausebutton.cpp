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

void okPlayPauseButton::setExternalTransitions(okVLCWrapper *vlc)
{
    play->addTransition(vlc, SIGNAL(played()), pause);
    pause->addTransition(vlc, SIGNAL(paused()), play);
    pause->addTransition(vlc, SIGNAL(stopped()), play);

    connect(play, SIGNAL(propertiesAssigned()), vlc, SLOT(pause()));
    connect(pause, SIGNAL(propertiesAssigned()), vlc, SLOT(play()));
}

okPlayPauseButton::~okPlayPauseButton()
{
    delete play;
    delete pause;
}
