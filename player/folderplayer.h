#ifndef FOLDERPLAYER_H
#define FOLDERPLAYER_H

#include <QObject>
#include "folderscanner.h"

class FolderPlayer : public QObject
{
    Q_OBJECT
public:
    explicit FolderPlayer(QObject *parent = 0);
    ~FolderPlayer();
    void play(const QString &path, bool recursive=false, bool append=false);
    void play(const QStringList &folderList, bool recursive=false, bool append=false);

signals:
    void scanPathChanged(QString);
    void finished(int);
    void cancelled();
    
private slots:
    void onFileListReady(const QList<QUrl> &filelist);
    void cancel();

private:
    FolderScanner   m_folderScanner;
    bool            m_toAppend;
    
};

#endif // FOLDERPLAYER_H
