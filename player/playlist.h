#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(QObject *parent=0);
    explicit Playlist(const QList<QUrl> &other, QObject *parent=0);

    void append(const QUrl &t);
    void append(const QList<QUrl> &other);

    const QUrl &at(int i) const;

    int count() const;
    int uniqueCount() const;
    int count(const QUrl &t) const;

    int indexOf(const QUrl &t, int from=0) const;
    bool isEmpty() const;
    bool contains(const QUrl &t) const;

    void removeAt(int i, int count = 1);
    int removeAll(const QUrl &t);

    QList<QUrl> urls() const;
    QList<QUrl> uniqueUrls() const;

    QString name() const;
    void setName(const QString &name);

    QList<QUrl> localTracks() const;

    void saveM3u(const QString &fileName) const;
    static QList<QUrl> fromM3u(const QString &fileName);

signals:
    void added();
    void removed(int i, int count);
    void countChanged();

protected:
    QString     m_name;
    QList<QUrl> m_urls;
};

#endif // PLAYLIST_H
