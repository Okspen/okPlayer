#ifndef OKPLAYLIST_H
#define OKPLAYLIST_H

#include <QStringList>
#include <QTextStream>
#include <QFile>

#include <QDebug>

class okPlaylist : public QStringList
{
public:
    okPlaylist();
    okPlaylist(const QString& fileName);
    okPlaylist(const QStringList& l);
    //сохраняет текущий плейлист в файл m3u
    void writeToFile(const QString& fileName);

    bool operator==(const okPlaylist& other) const;
};

#endif // OKPLAYLIST_H
