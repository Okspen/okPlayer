#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QUrl>
#include <QFileInfo>

class MediaInfo
{
public:
    MediaInfo(const QUrl &url);

    QString artist() const;
    QString album() const;
    QString title() const;

    QString fileName() const;
    QString ext() const;
    QUrl    url() const;
    QString searchString() const;

    bool isLocalFile() const;

    QString format(const QString &format) const;

    void setArtist(const QString &artist);
    void setAlbum(const QString &album);
    void setTitle(const QString &title);

protected:
    QString m_artist;
    QString m_album;
    QString m_title;

    QString m_fileName;
    QString m_extension;
    QUrl    m_url;

    QString m_searchString;

    void updateSearchString();
};

#endif // MEDIAINFO_H
