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

#include <QDebug>

class okPlayerDb : public QThread
{
public:
    okPlayerDb();
    ~okPlayerDb();

    void run();

    void createTables();
    void addTrack(QString path);
    void addTracks(const QList<QString>& tracks);

private:
    QSqlDatabase db;
    QList<QString> trs;

    int artistId(QString artist);
    int albumId(QString album, int artistId);
};

#endif // OKPLAYERDB_H
