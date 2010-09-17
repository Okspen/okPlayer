#ifndef OKVLCWRAPPER_H
#define OKVLCWRAPPER_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <vlc/vlc.h>

class okVLCWrapper : public QObject
{
	Q_OBJECT
public:
	okVLCWrapper();
	~okVLCWrapper();
	void setFile(const QString& path);
	int getVolume();
	//returns length in seconds
	qint64 getLength();
	double getPosition();
	bool isPlaying();
	bool isPaused();
	bool isStopped();
	bool isEnded();
	bool isFileSet();

public slots:
	void pause();
	void play();
	//void setTickInterval(qint32 newTickInterval);
	void stop();
	void setVolume(int newVol);
	void setPosition(int newPos);

private slots:
	void emitTick();

private:
	libvlc_instance_t *inst;
	libvlc_media_player_t *player;
	libvlc_media_t *currentFile;

    QString filePath;
	//timer for updating position
	QTimer timer;

	bool fileSet;

signals:
	void tick();
	void finished();
};

#endif // OKVLCWRAPPER_H
