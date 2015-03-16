#include "folderscanner.h"

FolderScanner::FolderScanner(QObject *parent) :
    QThread(parent),
    m_stop(false)
{
    m_lastScanDuration = 0;
    connect(this, SIGNAL(finished()), this, SLOT(processFound()));
}

void FolderScanner::run()
{
    QTime time;
    time.start();

    foreach (const QString &path, m_pathList)
        scanMedia(path);

    m_lastScanDuration = time.elapsed();

    if (!m_stop)
        emit scanFinished(m_lastScanDuration);
    else {
        emit scanCancelled();
        m_stop = false;
    }
}

void FolderScanner::setNameFilters(const QStringList &nameFilters)
{
    m_nameFilters = nameFilters;
}

int FolderScanner::lastScanDuration() const
{
    return m_lastScanDuration;
}

void FolderScanner::generateFileList(const QString &path, bool recursive)
{
    if (isRunning()) {
        quit();
        wait();
    }

    m_foundMedia.clear();
    m_pathList.clear();
    m_pathList.append(path);
    m_recursive = recursive;

    start();
}

void FolderScanner::generateFileList(const QStringList &pathList, bool recursive)
{
    if (isRunning()) {
        quit();
        wait();
    }

    m_foundMedia.clear();
    m_pathList.clear();
    m_pathList.append(pathList);
    m_recursive = recursive;

    start();
}

void FolderScanner::stop()
{
    m_stop = true;
    wait();
}

void FolderScanner::processFound()
{
    emit fileListReady(m_foundMedia);
}

void FolderScanner::scanMedia(const QString &path)
{
    if (m_stop) return;

    QFileInfo fileInfo(path);

    if (fileInfo.isFile()) {
        if (m_nameFilters.contains(QString("*.") + fileInfo.suffix().toLower()))
            m_foundMedia.append(QUrl::fromLocalFile(path));
        else if (path.right(3) == "m3u")
            m_foundMedia.append(Playlist::fromM3u(path));

        return;
    }

    emit scanPathChanged(path);

    QDir navigator(path);
    navigator.setNameFilters(m_nameFilters);
    navigator.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    const QFileInfoList &entries = navigator.entryInfoList();

    QString absolutePath;
    foreach (const QFileInfo &info, entries) {
        absolutePath = info.absoluteFilePath();
        if (info.isDir()) {
            if (m_recursive)
                scanMedia(absolutePath);
        } else {
            m_foundMedia.append(QUrl::fromLocalFile(absolutePath));
        }
    }
}
