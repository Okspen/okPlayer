#ifndef OKHDDTHREAD_H
#define OKHDDTHREAD_H

#include <QThread>
#include <QDir>
#include <QTime>

#include "okplaylist.h"

class okHddThread : public QThread
{
    Q_OBJECT
public:
    okHddThread();
    okHddThread(const QStringList& extensions, bool newAppend = false);
    void run();

    void setAppend(bool newAppend);
    void setPath(const QString &newPath);
    void setFileExt(const QStringList& extensions);
    void setOnlyRoot(bool newOnlyRoot);

    bool getAppend();
    okPlaylist* getPlaylist();

private:
    QStringList scanMediaFiles(const QString& path);

    int foldersCount;
    int totalFilesCount;
    int mediaFilesCount;

    QString path;
    QStringList fileExt;
    okPlaylist* playlist;

    QTime time;
    bool append;
    bool onlyRoot;

signals:
    void statsUpdated(int files, int total, int folders, QString time);
};

#endif // OKHDDTHREAD_H
