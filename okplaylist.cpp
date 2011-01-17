#include "okplaylist.h"

okPlaylist::okPlaylist()
{
}

okPlaylist::okPlaylist(const QStringList& l) : QStringList(l)
{
}

okPlaylist::okPlaylist(const QString& fileName)
{
    QFile file(fileName);
    //файл больше 3мб открывать опасно - плеер может упасть
    if(file.size() > 3*1000*1000)
    {
        qDebug() << fileName << "is too big";
        return;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString line;
    QTextStream textstr(&file);
    textstr.setCodec("UTF-8");
    while(!textstr.atEnd())
    {
        line = textstr.readLine();
        if(QFile::exists(line)) append(line);
        else qDebug() << line << "not exists";
    }
    file.close();
}

void okPlaylist::writeToFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    for(int i=0; i<count(); i++)
        out << at(i) << "\n";

    file.close();
}

bool okPlaylist::operator==(const okPlaylist& other) const
{
    int count1 = count();
    int count2 = other.count();
    if(count1 != count2) return false;

    for(int i=0; i<count1; i++)
        if(at(i) != other.at(i)) return false;

    return true;
}
