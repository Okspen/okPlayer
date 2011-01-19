#ifndef OKVLCWRAPPER_H
#define OKVLCWRAPPER_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <okplayerdb.h>
#include <vlc/vlc.h>

class okVLCWrapper : public QObject
{
    Q_OBJECT
public:
    okVLCWrapper();
    ~okVLCWrapper();
    void setFile(const QString& path);
    void setDb(okPlayerDb* newDb);
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
    void play();
    void pause();
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
    okPlayerDb* db;

    bool fileSet;

signals:
    void played();
    void paused();
    void stopped();
    void tick();
    void finished();
};

#endif // OKVLCWRAPPER_H
