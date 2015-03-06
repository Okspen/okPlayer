#include "mediainfo.h"

MediaInfo::MediaInfo(const QUrl &url)
{
    m_url = url;
    m_duration = 0;

    if (m_url.isLocalFile()) {
        QFileInfo fileInfo(url.toLocalFile());
        m_fileName = fileInfo.fileName();
        m_extension = fileInfo.suffix();
    }

    updateSearchString();
}

QString MediaInfo::artist() const
{
    return m_artist;
}

QString MediaInfo::album() const
{
    return m_album;
}

QString MediaInfo::title() const
{
    return m_title;
}

int MediaInfo::duration() const
{
    return m_duration;
}

QString MediaInfo::fileName() const
{
    return m_fileName;
}

QString MediaInfo::ext() const
{
    return m_extension;
}

QUrl MediaInfo::url() const
{
    return m_url;
}

QString MediaInfo::searchString() const
{
    return m_searchString;
}

bool MediaInfo::isLocalFile() const
{
    return m_url.isLocalFile();
}

QString MediaInfo::format(const QString &format) const
{
    QString result = format;

    QString artist;
    QString album;
    QString title;

    artist = m_artist.isEmpty() ? "Unknown Artist" : m_artist;
    album = m_album.isEmpty() ? "Unknown Album" : m_album;
    title = m_title.isEmpty() ? "Unknown Title" : m_title;

    result.replace("%artist", artist);
    result.replace("%album", album);
    result.replace("%title", title);

    return result;
}

void MediaInfo::setArtist(const QString &artist)
{
    m_artist = artist;
    updateSearchString();
}

void MediaInfo::setAlbum(const QString &album)
{
    m_album = album;
    updateSearchString();
}

void MediaInfo::setTitle(const QString &title)
{
    m_title = title;
    updateSearchString();
}

void MediaInfo::setDuration(int duration)
{
    m_duration = duration;
}

void MediaInfo::updateSearchString()
{
    m_searchString = m_title + m_album + m_artist + m_fileName;
}
