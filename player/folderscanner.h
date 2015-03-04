#ifndef FOLDERSCANNER_H
#define FOLDERSCANNER_H

#include <QThread>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "playlist.h"

/*
 * A class to scan file system and generate playlist.
 */
class FolderScanner : public QThread
{
    Q_OBJECT
public:
    explicit FolderScanner(QObject *parent = 0);
    void run();
    void setNameFilters(const QStringList& nameFilters);

signals:
    /* Emitted when playlist request completed */
    void fileListReady(QList<QUrl>);
    void scanPathChanged(QString);
    void scanFinished();
    void scanCancelled();

public slots:
    /* Starts the media-finding process. playlistReady() is emitted in the end */
    void generateFileList(const QString &path, bool recursive);
    void generateFileList(const QStringList &pathList, bool recursive);
    void stop();

private slots:
    /* Creates a playlist of found media */
    void processFound();

private:
    QStringList m_pathList;
    bool        m_recursive;
    bool        m_stop;
    /* The found media paths are stored here. It's cleared every time the media-finding process is started */
    QList<QUrl>    m_foundMedia;
    /* Only files with these extensions will be added to playlists */
    QStringList     m_nameFilters;

    void scanMedia(const QString &path);
};

#endif // FOLDERSCANNER_H
