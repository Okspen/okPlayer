#include "okplayerdb.h"
#include "taglib/tag.h"
#include "taglib/fileref.h"

okPlayerDb::okPlayerDb()
{
    isRunning = false;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+"/tracks.db");
    db.open();
    createTables();

    tracks = okPlaylist(QCoreApplication::applicationDirPath()+"/dbqueue.m3u");
    if(!tracks.isEmpty())
    {
        start();

    }
}

okPlayerDb::~okPlayerDb()
{
    if(!tracks.isEmpty()) tracks.writeToFile(QCoreApplication::applicationDirPath()+"/dbqueue.m3u");
    db.close();
}

void okPlayerDb::run()
{
    isRunning = true;
    setPriority(QThread::IdlePriority);
    while(!tracks.isEmpty())
    {
        addTrack(tracks.takeFirst());
        if(!isRunning) break;
    }
}

void okPlayerDb::stop()
{
    isRunning = false;
}

int okPlayerDb::left()
{
    return tracks.count();
}

void okPlayerDb::createTables()
{
    QSqlQuery sql(db);
    sql.exec("create table if not exists tracks (id integer primary key, title varchar(60) not null, artistId integer not null, albumId integer not null, path varchar(256) unique not null)");
    //qDebug() << sql.lastError().text();

    sql.exec("create table if not exists artists (id integer primary key, name varchar(256) unique not null)");
    //qDebug() << sql.lastError().text();

    sql.exec("create table if not exists albums (id integer primary key, name varchar(256) unique not null, artistId integer)");
    //qDebug() << sql.lastError().text();
}

void okPlayerDb::addTrack(QString path)
{
    QSqlQuery sql(db);
    sql.prepare("select id from tracks where path=:path");
    sql.bindValue(":path", path);
    sql.exec();
    if(sql.next()) return;

    QString album, artist, title;
    TagLib::FileRef f(path.toLocal8Bit().constData());
    if(!f.isNull())
    {
        album = f.tag()->album().toCString(true);
        artist = f.tag()->artist().toCString(true);
        title = f.tag()->title().toCString(true);
    }
    else qDebug() << "bad file:" << path.toLocal8Bit().constData();


    int tArtistId = artistId(artist);
    int tAlbumId = albumId(album, tArtistId);
    if(title.isEmpty()) title = path.split("/").last();

    sql.prepare("insert into tracks values(null, :title, :artistId, :albumId, :path)");
    sql.bindValue(":title", title);
    sql.bindValue(":artistId", tArtistId);
    sql.bindValue(":albumId", tAlbumId);
    sql.bindValue(":path", path);
    sql.exec();
}

void okPlayerDb::addTracks(okPlaylist* newPlaylist)
{
    tracks.append(static_cast<QStringList>(*newPlaylist));
    start();
}

int okPlayerDb::artistId(QString artist)
{
    if(artist.isEmpty()) artist = "Unknown artist";
    QSqlQuery sql;
    sql.prepare("select id from artists where name=:artist");
    sql.bindValue(":artist", artist);
    sql.exec();
    if(!sql.next())
    {
        sql.prepare("insert into artists values(null, :artist)");
        sql.bindValue(":artist", artist);
        if(!sql.exec())
        {
            qDebug() << sql.executedQuery();
            qDebug() << "artistId failed:" << sql.lastError().text();
        }
        return sql.lastInsertId().toInt();
    }
    return sql.value(0).toInt();
}

int okPlayerDb::albumId(QString album, int artistId)
{
    QSqlQuery sql(db);

    if(album.isEmpty())
    {
        album = "Unknown album";
        sql.prepare("select id from albums where name=:album");
        sql.bindValue(":album", album);
        sql.exec();
    }
    else
    {
        sql.prepare("select id from albums where name=:album and artistId=:artistId");
        sql.bindValue(":album", album);
        sql.bindValue(":artistId", artistId);
        sql.exec();
    }

    if(!sql.next())
    {
        sql.prepare("insert into albums values(null, :album, :artistId)");
        sql.bindValue(":album", album);
        sql.bindValue(":artistId", artistId);
        if(!sql.exec())
        {
            qDebug() << sql.executedQuery();
            qDebug() << "albumId failed:" << sql.lastError().text();
        }
        return sql.lastInsertId().toInt();
    }
    return sql.value(0).toInt();
}
