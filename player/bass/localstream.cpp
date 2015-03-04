#include "localstream.h"

using namespace BASS;

LocalStream::LocalStream(const QUrl &url, QObject *parent)
    : Stream(url, parent)
{
    prepare();
}

LocalStream::~LocalStream()
{
    if (m_stream != 0)
        BASS_StreamFree(m_stream);
}

bool LocalStream::prepare()
{
    QString path = m_url.toLocalFile();

    if (QFile::exists(path) == false)
        return false;

    if (m_stream != 0)
        BASS_StreamFree(m_stream);

    m_audioData.setFileName(path);
    if (m_audioData.open(QIODevice::ReadOnly) == false)
        return false;

    BASS_FILEPROCS  bassFileProcs = {fileClose, fileLen, fileRead, fileSeek};
    m_stream =
        BASS_StreamCreateFileUser(STREAMFILE_NOBUFFER, 0, &bassFileProcs, &m_audioData);

    if (m_stream != 0) {
        BASS_ChannelSetSync(m_stream, BASS_SYNC_END, 0, trackFinished, this);
        setVolume(m_volume);
        return true;
    }

    return false;
}

void LocalStream::fileClose(void *user)
{
    QFile *file = static_cast<QFile*>(user);
    file->close();
}

QWORD LocalStream::fileLen(void *user)
{
    QFile *file = static_cast<QFile*>(user);
    return file->size();
}

DWORD LocalStream::fileRead(void *buffer, DWORD length, void *user)
{
    QFile *file = static_cast<QFile*>(user);
    return file->read((char*) buffer, length);
}

BOOL LocalStream::fileSeek(QWORD offset, void *user)
{
    QFile *file = static_cast<QFile*>(user);
    return file->seek(offset);
}
