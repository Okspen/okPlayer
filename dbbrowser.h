#ifndef DBBROWSER_H
#define DBBROWSER_H

#include <QDialog>
#include <QMessageBox>
#include <okplayerdb.h>
#include <QSqlRecord>
#include <QTime>
#include <QFile>
#include <QPalette>
#include <QTreeWidget>
#include <QMenu>
#include "taglib/tag.h"
#include "taglib/fileref.h"
#include <statsdialog.h>

namespace Ui {
    class dbBrowser;
}

class dbBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit dbBrowser(QWidget *parent = 0);
    ~dbBrowser();
    void setDb(okPlayerDb* newDb);

private slots:
    void saveArtist();
    void saveAlbum();
    void saveTrack();

    void fillArtists();
    void fillAlbums();
    void fillTracks();
    void fillEditableData();

    void refreshDb();

    void truncateDb();
    void removeFile();
    void removeRecord();
    void search();

    void showStats();

private:
    Ui::dbBrowser *ui;
    okPlayerDb* db;
    QList<int> albumIds;
    QList<int> artistIds;
    QList<int> trackIds;
    QList<QString> tracks;

    void createMenu();
    void fillSearchResultsSection(QString title, QSqlQuery q);
};

#endif // DBBROWSER_H
