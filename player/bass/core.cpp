#include "player/bass/core.h"

using namespace BASS;

Core::Core(QObject *parent)
    : QObject(parent)
{
    m_stream = 0;
    m_volume = 100;
    m_volumeStep = 10;
    m_muted = false;
    m_looped = false;

    m_positionTimer = new QTimer(this);
    connect(m_positionTimer, SIGNAL(timeout()), this, SLOT(emitPosition()));

    m_delayTimer = new QTimer(this);
    m_delayTimer->setSingleShot(true);
    connect(m_delayTimer, SIGNAL(timeout()), this, SLOT(playDelayed()));
}

void Core::init(WId hwnd)
{
    loadPlugin("bassflac.dll", 0);
    loadPlugin("basswma.dll", 0);
    loadPlugin("bass_aac.dll", 0);
    loadPlugin("bass_ac3.dll", 0);
    loadPlugin("bass_alac.dll", 0);
    loadPlugin("bass_ape.dll", 0);
    m_initialized = BASS_Init(-1, 44100 ,0, (HWND) hwnd, NULL);

    if (m_initialized == false) {
        qDebug() << "BASS Error:";

        switch (BASS_ErrorGetCode()) {
        case BASS_ERROR_DX:
            qDebug() << "DirectX (or ALSA on Linux or OpenSL ES on Android) is not installed.";
        break;
        case BASS_ERROR_DEVICE:
            qDebug() << "Device is invalid.";
        break;
        case BASS_ERROR_ALREADY:
            qDebug() << "The device has already been initialized. BASS_Free must be called before it can be initialized again.";
            break;
        case BASS_ERROR_DRIVER:
            qDebug() << "There is no available device driver. The device may already be in use.";
        break;
        case BASS_ERROR_FORMAT:
            qDebug() << "The specified format is not supported by the device. Try changing the freq and flags parameters.";
        break;
        case BASS_ERROR_MEM:
            qDebug() << "There is insufficient memory.";
        break;
        case BASS_ERROR_NO3D:
            qDebug() << "Could not initialize 3D support.";
        break;
        case BASS_ERROR_UNKNOWN:
            qDebug() << "Some other mystery problem!";
        break;
        }
    }
}

Core::~Core()
{
    BASS_Free();
}

bool Core::isMuted() const
{
    return m_muted;
}

bool Core::isLooped() const
{
    return m_looped;
    //return BASS_ChannelFlags(m_stream, 0, 0) & BASS_SAMPLE_LOOP;
}

int Core::volume() const
{
    return m_volume;
}

qreal Core::position() const
{
    if (m_stream == 0)
        return 0;

    return m_stream->position();
}

void Core::timerEvent(QTimerEvent *e)
{
    emit positionChanged(positionSeconds(), lengthSeconds());
}

void Core::play()
{
    if (m_stream == 0)
        return;

    m_stream->play();
    if (m_stream->isPlaying()) {
        emit played();
        emit positionChanged(positionSeconds(), lengthSeconds());
    }
    m_positionTimer->start(500);
}

void Core::togglePlayPause()
{
    if (m_stream == 0)
        return;

    if (m_stream->isPlaying()) {
        pause();
    } else if (m_stream->isPaused()) {
        play();
    }
}

void Core::loadPlugin(const char *file, DWORD flags)
{
    HPLUGIN handle = BASS_PluginLoad(file, flags);
    if (handle == 0)
        qDebug() << QString("BASS Error: could not load plugin %1").arg(file);
}

QString Core::errorString(int code) const
{
    QString error;

    switch(code) {
    case BASS_OK:
        error = "all is OK";
        break;
    case BASS_ERROR_MEM:
        error = "memory error";
        break;
    case BASS_ERROR_FILEOPEN:
        error = "can't open the file";
        break;
    case BASS_ERROR_DRIVER:
        error = "can't find a free/valid driver";
        break;
    case BASS_ERROR_BUFLOST:
        error = "the sample buffer was lost";
        break;
    case BASS_ERROR_HANDLE:
        error = "invalid handle";
        break;
    case BASS_ERROR_FORMAT:
        error = "unsupported sample format";
        break;
    case BASS_ERROR_POSITION:
        error = "invalid position";
        break;
    case BASS_ERROR_INIT:
        error = "BASS_Init has not been successfully called";
        break;
    case BASS_ERROR_START:
        error = "BASS_Start has not been successfully called";
        break;
    case BASS_ERROR_ALREADY:
        error = "already initialized/paused/whatever";
        break;
    case BASS_ERROR_NOCHAN:
        error = "can't get a free channel";
        break;
    case BASS_ERROR_ILLTYPE:
        error = "an illegal type was specified";
        break;
    case BASS_ERROR_ILLPARAM:
        error = "an illegal parameter was specified";
        break;
    case BASS_ERROR_NO3D:
        error = "no 3D support";
        break;
    case BASS_ERROR_NOEAX:
        error = "no EAX support";
        break;
    case BASS_ERROR_DEVICE:
        error = "illegal device number";
        break;
    case BASS_ERROR_NOPLAY:
        error = "not playing";
        break;
    case BASS_ERROR_FREQ:
        error = "illegal sample rate";
        break;
    case BASS_ERROR_NOTFILE:
        error = "the stream is not a file stream";
        break;
    case BASS_ERROR_NOHW:
        error = "no hardware voices available";
        break;
    case BASS_ERROR_EMPTY:
        error = "the MOD music has no sequence data";
        break;
    case BASS_ERROR_NONET:
        error = "no internet connection could be opened";
        break;
    case BASS_ERROR_CREATE:
        error = "couldn't create the file";
        break;
    case BASS_ERROR_NOFX:
        error = "effects are not available";
        break;
    case BASS_ERROR_NOTAVAIL:
        error = "requested data is not available";
        break;
    case BASS_ERROR_DECODE:
        error = "the channel is/isn't a \"decoding channel\"";
        break;
    case BASS_ERROR_DX:
        error = "a sufficient DirectX version is not installed";
        break;
    case BASS_ERROR_TIMEOUT:
        error = "connection timed out";
        break;
    case BASS_ERROR_FILEFORM:
        error = "unsupported file format";
        break;
    case BASS_ERROR_SPEAKER:
        error = "unavailable speaker";
        break;
    case BASS_ERROR_VERSION:
        error = "invalid BASS version (used by add-ons)";
        break;
    case BASS_ERROR_CODEC:
        error = "codec is not available/supported";
        break;
    case BASS_ERROR_ENDED:
        error = "the channel/file has ended";
        break;
    case BASS_ERROR_BUSY:
        error = "the device is busy";
        break;
    case BASS_ERROR_UNKNOWN:
        error = "some other mystery problem";
        break;
    }
    return error;
}

void Core::play(const QUrl &url)
{
    if (url.isValid() == false)
        return;

    stop();

    int delay = 300;
    if (url.isLocalFile())
        delay = 50;

    m_delayedUrl = url;
    m_delayTimer->start(delay);

    emit positionChanged(0, 0);
}

void Core::pause()
{
    if (m_stream == 0)
        return;

    m_stream->pause();
    emit paused();
    m_positionTimer->stop();
}

void Core::stop()
{
    if (m_stream == 0)
        return;

    m_stream->stop();
    emit positionChanged(0, lengthSeconds());
    m_positionTimer->stop();
}

void Core::setPosition(qreal position)
{
    if (m_stream == 0)
        return;

    m_stream->setPosition(position);
}

void Core::setVolume(int volume)
{
    if (volume == m_volume)
        return;

    m_volume = qBound(0, volume, 100);
    if (m_stream != 0)
        m_stream->setVolume((qreal) volume/100);

    setMute(false);
    emit volumeChanged(m_volume);
}

void Core::setMute(bool enabled)
{
    if (m_muted == enabled)
        return;

    m_muted = enabled;
    if (m_stream != 0)
        m_stream->setMuted(enabled);

    emit muteToggled(enabled);
}

void Core::volumeUp()
{
    setVolume(m_volume + m_volumeStep);
}

void Core::volumeDown()
{
    setVolume(m_volume - m_volumeStep);
}

void Core::setLoop(bool loop)
{
    if (m_looped == loop)
        return;

    m_looped = loop;
    if (m_stream != 0)
        m_stream->setLooped(loop);

    emit loopChanged(m_looped);
}

double Core::positionSeconds() const
{
    if (m_stream == 0)
        return 0;

    return m_stream->positionSeconds();
}

qint32 Core::length() const
{
    if (m_stream == 0)
        return 0;

    return m_stream->length();
}

double Core::lengthSeconds() const
{
    if (m_stream == 0)
        return 0;

    return m_stream->lengthSeconds();
}

QString Core::timeToString(qint32 position, qint32 total)
{
    QTime timeTime = QTime(0,0).addSecs(position);

    QString format = "mm:ss";
    if (total >= 3600 * 1000) // more than hour in ms
        format = "h:mm:ss";

    return timeTime.toString(format);
}

void Core::playDelayed()
{
    if (!m_initialized || !m_delayedUrl.isValid())
        return;

    if (m_stream != 0) {
        stop();
        disconnect(m_stream, SIGNAL(finished()), this, SLOT(onFinished()));
        delete m_stream;
    }

    m_stream = new LocalStream(m_delayedUrl, this);
    connect(m_stream, SIGNAL(finished()), this, SLOT(onFinished()));

    m_stream->setVolume((qreal)m_volume/100);
    m_stream->setMuted(m_muted);
    m_stream->setLooped(m_looped);

    play();
}

void Core::onFinished()
{
    if (!isLooped())
        emit finished();
}

void Core::emitPosition()
{
    emit positionChanged(positionSeconds(), lengthSeconds());
}
