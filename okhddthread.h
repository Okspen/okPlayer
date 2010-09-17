#ifndef OKHDDTHREAD_H
#define OKHDDTHREAD_H

#include <QThread>
#include <QDir>
#include <QTime>

class okHDDThread : public QThread
{
	Q_OBJECT
public:
    okHDDThread();
	okHDDThread(QStringList extensions, bool newAppend = false);
	void run();

	void setPath(const QString &newPath);
	void setFileExt(const QStringList& extensions);
	void setOnlyRoot(bool newOnlyRoot);

	bool getAppend();
	QStringList getPlaylist();

private:
	QStringList scanMediaFiles(const QString& path);

	int foldersCount;
	int totalFilesCount;
	int mediaFilesCount;

	QString path;
	QStringList fileExt;
	QStringList playlist;

	QTime time;
	bool append;
	bool onlyRoot;

signals:
	void statsUpdated(int files, int total, int folders, QString time);
};

#endif // OKHDDTHREAD_H
