#ifndef BASSPLAYER_H
#define BASSPLAYER_H

#include "bass/c/bass.h"
#include <QWidget>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QThread>
#include "player/bass/localstream.h"
#include "player/playersettings.h"

namespace BASS {
class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent=0);
    ~Core();

    bool isMuted() const;
    bool isPlaying() const;
    bool isPaused() const;
    bool isLooped() const;

    int volume() const;

    qreal position() const;
    double positionSeconds() const;

    qint32 length() const;
    double lengthSeconds() const;

    static QString timeToString(qint32 position, qint32 total);

protected:
    void timerEvent(QTimerEvent *e);

signals:
    void volumeChanged(int);
    void muteToggled(bool);
    void loopChanged(bool);
    void played();
    void paused();
    void finished();
    void positionChanged(qint32, qint32);

public slots:
    void init(WId hwnd=0);
    void play();
    void togglePlayPause();
    void play(const QUrl &url);
    void pause();
    void stop();
    void setPosition(qreal position);
    void setLoop(bool loop);

    void setVolume(int volume);
    void setMute(const bool enabled);

    void volumeUp();
    void volumeDown();

private:
    bool    m_initialized;

    int     m_volume;
    int     m_volumeStep;
    bool    m_muted;
    bool    m_looped;

    Stream  *m_stream;

    QTimer  *m_positionTimer;
    QTimer  *m_delayTimer;
    QUrl    m_delayedUrl;

    bool prepare(const QUrl &url);
    void loadPlugin(const char *file, DWORD flags);
    QString errorString(int code) const;

private slots:
    void playDelayed();
    void onFinished();
    void emitPosition();
};
}

#endif // BASSPLAYER_H
