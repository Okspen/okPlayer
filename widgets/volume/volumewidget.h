#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QWidget>
#include "player/bass/core.h"

namespace Ui {
class VolumeWidget;
}

class VolumeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit VolumeWidget(QWidget *parent = 0);
    ~VolumeWidget();

public slots:
    void volumeUp();
    void volumeDown();
    void setVolume(int value);
    void setMute(bool mute);

signals:
    void volumeChanged(int);
    void muteToggled(bool);
    
private:
    Ui::VolumeWidget *ui;
    int m_volumeStep;
};

#endif // VOLUMEWIDGET_H
