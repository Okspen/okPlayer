#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QToolButton>
#include <QSlider>

#include <QDebug>

class VolumeButton : public QToolButton
{
    Q_OBJECT
public:
    explicit VolumeButton(QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void muteToggled(bool);

public slots:
    void setMute(bool status);
    void adjustIcon(int volume);

private:
    QIcon   m_muteIcon;
    QIcon   m_lowIcon;
    QIcon   m_mediumIcon;
    QIcon   m_highIcon;

    bool    m_muteStatus;
    int     m_lastVolume;
};

#endif // VOLUMEBUTTON_H
