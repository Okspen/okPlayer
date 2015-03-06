#include "tagreader.h"

TagReader::TagReader(QObject *parent) :
    QObject(parent),
    m_cancel(false)
{
}

void TagReader::setList(QList<MediaInfo *> list)
{
    m_queue = list;
}

void TagReader::readTagsBASS(MediaInfo *info)
{
    QUrl url = info->url();

    if (!url.isLocalFile())
        return;

    QString path = url.toLocalFile();

    QFileInfo fileInfo(path);
    QString extension = fileInfo.suffix();

    QString artist;
    QString album;
    QString title;

    BASS::LocalStream bs(url, this);
    HSTREAM s = bs.handler();
    int seconds = bs.lengthSeconds();

    artist = TAGS_Read(s, "%UTF8(%ARTI)");
    album = TAGS_Read(s, "%UTF8(%ALBM)");
    title = TAGS_Read(s, "%UTF8(%TITL)");

    artist = artist.simplified();
    album = album.simplified();
    title = title.simplified();

    info->setAlbum(album);
    info->setArtist(artist);
    info->setTitle(title);
    info->setDuration(seconds);
}

void TagReader::process()
{
    m_cancel = false;
    MediaInfo *info = 0;

    for (int i=0; i<m_queue.count() && !m_cancel; ++i) {
        info = m_queue.at(i);
        readTagsBASS(info);
        emit processed(info);
    }

    emit finished();
}

void TagReader::cancel()
{
    m_cancel = true;
}
