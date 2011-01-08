#include "okhddthread.h"

okHddThread::okHddThread()
{
    append = false;
    onlyRoot = false;
}

okHddThread::okHddThread(const QStringList& extensions, bool newAppend)
{
    append = newAppend;
    setFileExt(extensions);
    onlyRoot = false;
}

void okHddThread::run()
{
    foldersCount = 1;
    mediaFilesCount = 0;
    totalFilesCount = 0;
    time.start();

    playlist = scanMediaFiles(path);
}

QStringList okHddThread::scanMediaFiles(const QString& path)
{
    QDir navigator(path);
    QStringList foundMediaSources;

    QString fileOrDir;
    QFileInfo fileOrDirInfo;
    QStringList entries = navigator.entryList();

    foreach(fileOrDir, entries)
    {
        fileOrDirInfo.setFile(navigator.absolutePath() + "/" + fileOrDir);
        if(fileOrDirInfo.isDir())
        {
            //запускаем рекурсивно и результаты пристыковываем к основному массиву
            if((fileOrDir != ".") && (fileOrDir != "..") && (onlyRoot == false))
            {
                foundMediaSources.append(scanMediaFiles(navigator.absolutePath() + "/" + fileOrDir));
                foldersCount++;
            }
        }
        else
        {
            if(fileExt.indexOf("*."+fileOrDirInfo.suffix().toLower()) != -1)
            {
                foundMediaSources << navigator.absoluteFilePath(fileOrDir);
                mediaFilesCount++;
            }
            totalFilesCount++;
            emit statsUpdated(mediaFilesCount, totalFilesCount, foldersCount, QTime().addMSecs(time.elapsed()).toString("mm:ss:zzz"));
        }
    }
    return foundMediaSources;
}

void okHddThread::setAppend(bool newAppend)
{
    append = newAppend;
}

void okHddThread::setPath(const QString &newPath)
{
    path = newPath;
}

QStringList okHddThread::getPlaylist()
{
    return playlist;
}

void okHddThread::setFileExt(const QStringList& extensions)
{
    if(!extensions.empty())
        fileExt = extensions;
}

bool okHddThread::getAppend()
{
    return append;
}

void okHddThread::setOnlyRoot(bool newOnlyRoot)
{
    onlyRoot = newOnlyRoot;
}
