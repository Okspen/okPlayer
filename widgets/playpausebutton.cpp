#include "playpausebutton.h"

PlayPauseButton::PlayPauseButton(QWidget *parent) :
    QToolButton(parent)
{
    play = new QState;
    play->assignProperty(this, "icon", QIcon(":/tango/images/icons/tango/media-playback-start.png"));
    play->assignProperty(this, "toolTip", "Play");
    play->setObjectName("play");

    pause = new QState;
    pause->assignProperty(this, "icon", QIcon(":/tango/images/icons/tango/media-playback-pause.png"));
    pause->assignProperty(this, "toolTip", "Pause");
    pause->setObjectName("pause");

    machine.addState(play);
    machine.addState(pause);
    machine.setInitialState(play);
    machine.start();

    connect(this, SIGNAL(clicked()), this, SLOT(processClick()));
}

void PlayPauseButton::setPlayer(BASS::Core *player)
{
    m_player = player;

    play->addTransition(m_player,   SIGNAL(played()), pause);
    pause->addTransition(m_player,  SIGNAL(paused()), play);

    connect(play,   SIGNAL(propertiesAssigned()), m_player, SLOT(pause()));
    connect(pause,  SIGNAL(propertiesAssigned()), m_player, SLOT(play()));
}

void PlayPauseButton::processClick()
{
    m_player->togglePlayPause();
}

PlayPauseButton::~PlayPauseButton()
{
    delete play;
    delete pause;
}
