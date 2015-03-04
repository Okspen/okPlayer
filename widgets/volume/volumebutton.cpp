#include "volumebutton.h"

VolumeButton::VolumeButton(QWidget *parent) :
    QToolButton(parent)
{
    m_muteIcon.addFile(":/tango/images/icons/tango/audio-volume-muted.png");
    m_lowIcon.addFile(":/tango/images/icons/tango/audio-volume-low.png");
    m_mediumIcon.addFile(":/tango/images/icons/tango/audio-volume-medium.png");
    m_highIcon.addFile(":/tango/images/icons/tango/audio-volume-high.png");

    setIcon(m_mediumIcon);

    m_muteStatus = false;
    m_lastVolume = 100;
}

void VolumeButton::setMute(bool status)
{
    if (status == m_muteStatus)
        return;

    m_muteStatus = status;

    if (m_muteStatus)
        setIcon(m_muteIcon);
    else
        adjustIcon(m_lastVolume);

    emit muteToggled(status);
}

void VolumeButton::mouseReleaseEvent(QMouseEvent *event)
{
    setMute(!m_muteStatus);
    QToolButton::mouseReleaseEvent(event);
}

void VolumeButton::adjustIcon(int volume)
{
    if (volume == 0) {
        setIcon(m_muteIcon);
    } else {
        if(volume >=1 && volume <= 33)
            setIcon(m_lowIcon);
        if(volume >=34 && volume <= 66)
            setIcon(m_mediumIcon);
        if(volume >= 67 && volume <=100)
            setIcon(m_highIcon);
    }

    m_lastVolume = volume;
}
