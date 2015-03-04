#ifndef TRACK_H
#define TRACK_H

#define TAGLIB_STATIC
#include <QFileInfo>
#include <QTextCodec>
#include <QUrl>
#include <QDebug>
#include "taglib/taglib.h"
#include "taglib/tag.h"
#include "taglib/fileref.h"
#include "taglib/mpegfile.h"
#include "taglib/id3v1tag.h"
#include "taglib/id3v2tag.h"

class Track
{
public:
    Track();
    Track(const QUrl& url);
    Track(const Track& track);

    QString artist() const;
    QString album() const;
    QString title() const;

    QString fileName() const;
    QString ext() const;
    QUrl    url() const;
    QString searchString() const;

    bool isLocal() const;

    QString format(const QString &format) const;

    void setArtist(const QString &artist);
    void setAlbum(const QString &album);
    void setTitle(const QString &title);
    void setUrl(const QUrl &url);

    void readTags();
    void refreshTags();

protected:
    QString m_artist;
    QString m_album;
    QString m_title;

    QString m_fileName;
    QString m_extension;
    QUrl m_url;

    QString m_searchString;
    bool m_tagsRead;

    void updateSearchString();
    QString toQString(const TagLib::String& str, TagLib::ID3v1::Tag *id3v1=0, TagLib::ID3v2::Tag *id3v2=0) const;
};

#endif // TRACK_H
