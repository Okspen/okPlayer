#include "okhddthread.h"

okHDDThread::okHDDThread()
{
	append = false;
	onlyRoot = false;
}

okHDDThread::okHDDThread(QStringList extensions, bool newAppend)
{
	append = newAppend;
	setFileExt(extensions);
}

void okHDDThread::run()
{
	foldersCount = 1;
	mediaFilesCount = 0;
	totalFilesCount = 0;
	time.start();

	playlist = scanMediaFiles(path);
}

QStringList okHDDThread::scanMediaFiles(const QString& path)
{
	QDir navigator(path);
	QStringList foundMediaSources;

	QStringList entries = navigator.entryList();
	QString fileOrDir;
	QFileInfo fileOrDirInfo;

	foreach(fileOrDir, entries)
	{
		fileOrDirInfo.setFile(navigator.absolutePath() + "/" + fileOrDir);
		if(fileOrDirInfo.isDir())
		{
			//запускаем рекурсивно и результаты пристыковываем к основному массиву
			if((fileOrDir != ".") && (fileOrDir != "..") && (onlyRoot != false))
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

void okHDDThread::setPath(const QString &newPath)
{
	path = newPath;
}

QStringList okHDDThread::getPlaylist()
{
	return playlist;
}

void okHDDThread::setFileExt(const QStringList& extensions)
{
	if(!extensions.empty())
		fileExt = extensions;
}

bool okHDDThread::getAppend()
{
	return append;
}

void okHDDThread::setOnlyRoot(bool newOnlyRoot)
{
	onlyRoot = newOnlyRoot;
}
