#include "playlist.h"

class Player;

Playlist::Playlist(QObject *parent)
    : QObject(parent)
{
}

Playlist::Playlist(const QList<QUrl> &other, QObject *parent)
    : QObject(parent)
{
    m_urls.append(other);
}

void Playlist::append(const QUrl &t)
{
    m_urls.append(t);
    emit countChanged();
}

void Playlist::append(const QList<QUrl> &other)
{
    m_urls.append(other);
    emit countChanged();
}

const QUrl &Playlist::at(int i) const
{
    return m_urls.at(i);
}

int Playlist::count() const
{
    return m_urls.count();
}

int Playlist::uniqueCount() const
{
    return m_urls.toSet().count();
}

int Playlist::count(const QUrl &t) const
{
    return m_urls.count(t);
}

int Playlist::indexOf(const QUrl &t, int from) const
{
    return m_urls.indexOf(t, from);
}

bool Playlist::isEmpty() const
{
    return m_urls.isEmpty();
}

bool Playlist::contains(const QUrl &t) const
{
    return m_urls.contains(t);
}

void Playlist::removeAt(int i, int count)
{
    if (count < 1)
        return;

    if (count == 1)
        m_urls.removeAt(i);

    if (count > 1)
        for (int r = 0; r < count; ++r)
            m_urls.removeAt(i);

    emit removed(i, count);
    emit countChanged();
}

int Playlist::removeAll(const QUrl &t)
{
    int r = m_urls.removeAll(t);
    emit countChanged();
    return r;
}

QList<QUrl> Playlist::urls() const
{
    return m_urls;
}

QList<QUrl> Playlist::uniqueUrls() const
{
    return m_urls.toSet().toList();
}

void Playlist::setName(const QString &name)
{
    m_name = name;
}

QList<QUrl> Playlist::localTracks() const
{
    QList<QUrl> tracks;
    for (int i=0; i<count(); i++) {
        if (m_urls.at(i).isLocalFile())
            tracks.append(at(i));
    }
    return tracks;
}

QString Playlist::name() const
{
    return m_name;
}

void Playlist::saveM3u(const QString &fileName) const
{
    if (fileName.isEmpty())
        return;

    QFile::remove(fileName);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    QUrl url;
    for (int i=0; i<count(); i++) {
        url = at(i);
        if (url.isLocalFile())
            out << url.toLocalFile() << "\n";
        else
            out << url.toString() << "\n";
    }

    file.close();
}

QList<QUrl> Playlist::fromM3u(const QString &fileName)
{
    QList<QUrl> fileList;

    if (fileName.right(3) != "m3u")
        return fileList;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return fileList;

    QUrl    url;
    QString line;

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    while (!stream.atEnd()) {
        line = stream.readLine();
        if (QFile::exists(line)) {
            fileList.append(QUrl::fromLocalFile(line));
        } else {
            url.setUrl(line);
            if (url.isValid())
                fileList.append(url);
        }
    }
    file.close();
    return fileList;
}
