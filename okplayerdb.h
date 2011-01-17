#ifndef OKPLAYERDB_H
#define OKPLAYERDB_H

#include <QApplication>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QThread>
#include <QTime>
#include <QVariant>
#include "okplaylist.h"

#include <QDebug>

class okPlayerDb : public QThread
{
public:
    okPlayerDb();
    ~okPlayerDb();

    void run();
    void stop();
    int left();

    void createTables();
    void addTrack(QString path);
    void addTracks(okPlaylist* playlist);

private:
    QSqlDatabase db;
    okPlaylist tracks;
    bool isRunning;

    int artistId(QString artist);
    int albumId(QString album, int artistId);
};

#endif // OKPLAYERDB_H
