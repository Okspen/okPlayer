#include "stream.h"

using namespace BASS;

Stream::Stream(QObject *parent) :
    QObject(parent),
    m_stream(0),
    m_muted(false),
    m_volume(1)
{
}

Stream::Stream(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_stream(0),
    m_muted(false),
    m_volume(1)
{
    m_url = url;
}

void Stream::play()
{
    BASS_ChannelPlay(m_stream, false);
}

void Stream::pause()
{
    BASS_ChannelPause(m_stream);
}

void Stream::stop()
{
    BASS_ChannelStop(m_stream);
}

float Stream::volume() const
{
    float vol;
    BASS_ChannelGetAttribute(m_stream, BASS_ATTRIB_VOL, &vol);
    return vol;
}

void Stream::setVolume(float volume)
{
    BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, volume);
}

void Stream::setMuted(bool m)
{
    if (m == m_muted)
        return;

    m_muted = m;
    if (m_muted) {
        m_volume = volume();
        BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, 0);
    } else {
        BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, m_volume);
    }
}

qreal Stream::position() const
{
    if (m_stream == 0)
        return 0;

    QWORD pos = BASS_ChannelGetPosition(m_stream, BASS_POS_BYTE);
    if (pos == -1)
        pos = 0;

    return pos / length();
}

double Stream::positionSeconds() const
{
    if (m_stream == 0)
        return 0;
    return BASS_ChannelBytes2Seconds
            (m_stream, BASS_ChannelGetPosition(m_stream, BASS_POS_BYTE));
}

void Stream::setPosition(qreal position)
{
    if (m_stream == 0)
        return;
    BASS_ChannelSetPosition(m_stream, position * length(), BASS_POS_BYTE);
}

bool Stream::looped() const
{
    return BASS_ChannelFlags(m_stream, 0, 0) & BASS_SAMPLE_LOOP;
}

void Stream::setLooped(bool value)
{
    if (value)
        BASS_ChannelFlags(m_stream, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
    else
        BASS_ChannelFlags(m_stream, 0, BASS_SAMPLE_LOOP);
}

QWORD Stream::length(DWORD mode) const
{
    return BASS_ChannelGetLength(m_stream, mode);
}

double Stream::lengthSeconds() const
{
    return BASS_ChannelBytes2Seconds(m_stream, length());
}

HSTREAM Stream::handler() const
{
    return m_stream;
}

void Stream::emitFinished()
{
    emit finished();
}

void Stream::trackFinished(HSYNC handle, DWORD channel, DWORD data, void *user)
{
    Q_UNUSED(data);
    Q_UNUSED(channel);
    Q_UNUSED(handle);

    Stream* s = static_cast<Stream*>(user);
    s->emitFinished();
}

bool Stream::isPlaying() const
{
    return (BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PLAYING);
}

bool Stream::isPaused() const
{
    return (BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PAUSED);
}

bool Stream::isMuted() const
{
    float vol;
    BASS_ChannelGetAttribute(m_stream, BASS_ATTRIB_VOL, &vol);
    return vol==0;
}
