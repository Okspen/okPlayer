#include "track.h"

Track::Track()
{
    m_tagsRead = false;
}

Track::Track(const QUrl &url)
{
    m_tagsRead = false;
    m_url = url;

    if (isLocal()) {
        QFileInfo fileInfo(m_url.toLocalFile());
        m_fileName = fileInfo.fileName();
        m_extension = fileInfo.suffix();
    }

    updateSearchString();
}

Track::Track(const Track &track)
{
    m_url   = track.url();
    m_artist = track.artist();
    m_album = track.album();
    m_title = track.title();

    m_fileName = track.fileName();
    m_extension = track.ext();

    m_tagsRead = false;

    updateSearchString();
}

QString Track::artist() const
{
    return m_artist;
}

QString Track::album() const
{
    return m_album;
}

QString Track::title() const
{
    return m_title;
}

QString Track::fileName() const
{
    return m_fileName;
}

QString Track::ext() const
{
    return m_extension;
}

QUrl Track::url() const
{
    return m_url;
}

QString Track::searchString() const
{
    return m_searchString;
}

bool Track::isLocal() const
{
    return m_url.isLocalFile();
}

QString Track::format(const QString &format) const
{
    QString result = format;

    QString artist;
    QString album;
    QString title;

    artist = m_artist.isEmpty() ? "Unknown artist" : m_artist;
    album = m_album.isEmpty() ? "Unknown album" : m_album;
    title = m_title.isEmpty() ? "Unknown title" : m_title;

    result.replace("%artist", artist);
    result.replace("%album", album);
    result.replace("%title", title);

    return result;
}

void Track::setArtist(const QString &artist)
{
    m_artist = artist;
}

void Track::setAlbum(const QString &album)
{
    m_album = album;
}

void Track::setTitle(const QString &title)
{
    m_title = title;
}

void Track::setUrl(const QUrl &url)
{
    m_url = url;
    if (isLocal()) {
        QFileInfo fileInfo(m_url.toLocalFile());
        m_fileName = fileInfo.fileName();
        m_extension = fileInfo.suffix();
    }
}

void Track::updateSearchString()
{
    m_searchString = m_title + m_album + m_artist;
}

void Track::readTags()
{
    if (isLocal() == false || m_tagsRead == true)
        return;

    QString path = m_url.toLocalFile();

    if (m_extension == "mp3") {
        TagLib::MPEG::File mpegFile(path.toStdWString().c_str());
        if (!mpegFile.isValid())
            return;

        TagLib::ID3v1::Tag *id3v1 = 0;
        TagLib::ID3v2::Tag *id3v2 = 0;

        TagLib::Tag *tag = mpegFile.tag();
        if (tag == 0)
            return;

        id3v1 = mpegFile.ID3v1Tag();
        id3v2 = mpegFile.ID3v2Tag();

        m_artist = toQString(tag->artist(), id3v1, id3v2);
        m_title = toQString(tag->title(), id3v1, id3v2);
        m_album = toQString(tag->album(), id3v1, id3v2);
    } else {
        TagLib::FileRef file(path.toStdWString().c_str());
        if (file.isNull())
            return;

        TagLib::Tag *tag = file.tag();
        if (tag == 0)
            return;

        m_artist = toQString(tag->artist());
        m_title = toQString(tag->title());
        m_album = toQString(tag->album());
    }

    updateSearchString();
    m_tagsRead = true;
}

void Track::refreshTags()
{
    if (isLocal() == false)
        return;

    m_tagsRead = false;
    readTags();
}

QString Track::toQString(const TagLib::String &str, TagLib::ID3v1::Tag *id3v1, TagLib::ID3v2::Tag *id3v2) const
{
    if (str.isLatin1() && str.isAscii())
        return QString::fromLatin1(str.to8Bit().c_str());

    if (str.isLatin1() && !str.isAscii()) {
        const char *raw = str.toCString();
        QTextCodec *codec = 0;

        bool id3v1Empty = true;
        bool id3v2Empty = true;

        if (id3v1 != 0)
            id3v1Empty = id3v1->isEmpty();
        if (id3v2 !=0)
            id3v2Empty = id3v2->isEmpty();

        //qDebug() << str.to8Bit().c_str() << id3v1Empty << id3v2Empty;

        if (((id3v1Empty == false) && id3v2Empty)
                || (id3v1Empty && (id3v2Empty == false))
                || (id3v1Empty == false && id3v2Empty == false)) {
            codec = QTextCodec::codecForLocale();
            return codec->toUnicode(raw);
        }

        codec = QTextCodec::codecForName("ISO-8859-1");
        return codec->toUnicode(raw);
    }

    return QString::fromStdWString(str.toWString());
}
