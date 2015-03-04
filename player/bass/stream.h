#ifndef STREAM_H
#define STREAM_H

#include "bass/bass.h"
#include <QObject>
#include <QFile>
#include <QUrl>

namespace BASS {
class Stream : public QObject
{
    Q_OBJECT
public:
    Stream(QObject *parent=0);
    Stream(const QUrl &url, QObject *parent=0);

    bool isPlaying() const;
    bool isPaused() const;
    bool isMuted() const;

    void play();
    void pause();
    void stop();

    float volume() const;
    void setVolume(float volume);
    void setMuted(bool m);

    qreal position() const;
    double positionSeconds() const;
    void setPosition(qreal position);

    bool looped() const;
    void setLooped(bool value);

    QWORD length(DWORD mode=BASS_POS_BYTE) const;
    double lengthSeconds() const;

    HSTREAM handler() const;

signals:
    void finished();

protected:
    QUrl    m_url;
    HSTREAM m_stream;

    bool m_muted;
    qreal m_volume;

    void emitFinished();
    static void CALLBACK trackFinished(HSYNC handle, DWORD channel, DWORD data, void *user);
};
}

#endif // STREAM_H
