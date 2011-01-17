#include "dbbrowser.h"
#include "ui_dbbrowser.h"

dbBrowser::dbBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dbBrowser)
{
    ui->setupUi(this);

    //connect(ui->tracksTable, SIGNAL(itemSelectionChanged()), this, SLOT(fillTrackData()));
    //connect(ui->save, SIGNAL(clicked()), this, SLOT(saveData()));
    //connect(ui->truncateDb, SIGNAL(clicked()), this, SLOT(truncateDb()));
    //connect(ui->removeFile, SIGNAL(clicked()), this, SLOT(removeFile()));
    //connect(ui->removeRecord, SIGNAL(clicked()), this, SLOT(removeRecord()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->searchEdit, SIGNAL(returnPressed()), this, SLOT(search()));
    connect(ui->statsButton, SIGNAL(clicked()), this, SLOT(showStats()));

    connect(ui->artistSaveButton, SIGNAL(clicked()), this, SLOT(saveArtist()));
    connect(ui->albumSaveButton, SIGNAL(clicked()), this, SLOT(saveAlbum()));
    connect(ui->trackSaveButton, SIGNAL(clicked()), this, SLOT(saveTrack()));

    connect(ui->artistsTable, SIGNAL(itemSelectionChanged()), this, SLOT(fillEditableData()));
    connect(ui->albumsTable, SIGNAL(itemSelectionChanged()), this, SLOT(fillEditableData()));
    connect(ui->tracksTable, SIGNAL(itemSelectionChanged()), this, SLOT(fillEditableData()));

    countTotals();

    timer.start(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(fillThreadData()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(fillArtists()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(fillAlbums()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(fillTracks()));

    refreshDb();
}

dbBrowser::~dbBrowser()
{
    delete ui;
}

void dbBrowser::setDb(okPlayerDb* newDb)
{
    db = newDb;
}

void dbBrowser::saveArtist()
{
    int row=0;
    if(!ui->artistsTable->selectedItems().isEmpty())
        row = ui->artistsTable->selectedItems().first()->row();
    else return;

    QSqlQuery q;
    q.exec(QString("update artists set name='%2' where id=%1").arg(row).arg(ui->artistEdit->text()));
    if(q.isActive())
        ui->artistsTable->selectedItems().first()->setText(ui->artistEdit->text());
    else qDebug() << q.lastError().text();
}

void dbBrowser::saveAlbum()
{
    int row=0;
    if(!ui->albumsTable->selectedItems().isEmpty())
        row = ui->albumsTable->selectedItems().first()->row();
    else return;

    QSqlQuery q;
    q.exec(QString("update albums set name='%2' where id=%1").arg(row).arg(ui->artistEdit->text()));
    if(q.isActive())
        ui->albumsTable->selectedItems().first()->setText(ui->albumEdit->text());
    else qDebug() << q.lastError().text();
}

void dbBrowser::saveTrack()
{
    int row=0;
    if(!ui->tracksTable->selectedItems().isEmpty())
        row = ui->tracksTable->selectedItems().first()->row();
    else return;

    QSqlQuery q;
    q.exec(QString("update tracks set title='%2' where id=%1").arg(row).arg(ui->artistEdit->text()));
    if(q.isActive())
        ui->tracksTable->selectedItems().first()->setText(ui->trackEdit->text());
    else qDebug() << q.lastError().text();
}

void dbBrowser::fillArtists()
{
    int start = ui->artistsTable->rowCount()+1;
    if(start >= totalArtists) return;

    QSqlQuery sql;
    sql.prepare("select id, name from artists limit :start, :end");
    sql.bindValue(":start", start);
    sql.bindValue(":end", start+250);

    if(!sql.exec())
        qDebug() << "Query exec() error." << sql.lastError();

    ui->artistsTable->setRowCount(0);
    ui->artistsTable->setColumnCount(1);

    int row = start-1;
    QTableWidgetItem* temp=0;

    while (sql.next())
    {
        ui->artistsTable->insertRow(row);
        temp = new QTableWidgetItem(sql.value(1).toString());
        temp->setFlags(temp->flags() & (~Qt::ItemIsEditable));

        ui->artistsTable->setItem(row,0,temp);
        artistIds.append(sql.value(0).toInt());
        row++;
    }
}

void dbBrowser::fillAlbums()
{
    int start = ui->albumsTable->rowCount()+1;
    if(start >= totalAlbums) return;

    QSqlQuery sql;
    sql.prepare("select id, name from albums limit :start, :end");
    sql.bindValue(":start", start);
    sql.bindValue(":end", start+250);

    if(!sql.exec())
        qDebug() << "Query exec() error." << sql.lastError();

    ui->albumsTable->setRowCount(0);
    ui->albumsTable->setColumnCount(1);
    int row = 0;
    QTableWidgetItem* temp=0;
    while (sql.next())
    {
        ui->albumsTable->insertRow(row);
        temp = new QTableWidgetItem(sql.value(1).toString());
        temp->setFlags(temp->flags() & (~Qt::ItemIsEditable));

        ui->albumsTable->setItem(row, 0, temp);
        albumIds.append(sql.value(1).toInt());
        row++;
    }
}

void dbBrowser::fillTracks()
{
    int start = ui->tracksTable->rowCount()+1;
    qDebug() << start << totalTracks;
    if(start >= totalTracks) return;

    QSqlQuery sql;
    sql.prepare("select tracks.id, tracks.title, artists.name, albums.name from tracks, artists, albums where albums.id=tracks.albumId and artists.id=tracks.artistId limit :start, :end");
    sql.bindValue(":start", start);
    sql.bindValue(":end", start+500);

    if(!sql.exec())
        qDebug() << "Query exec() error." << sql.lastError();

    ui->tracksTable->setRowCount(0);
    tracks.clear();
    int row = 0;
    QTableWidgetItem* temp=0;
    while (sql.next())
    {
        ui->tracksTable->insertRow(row);
        for(int i=1; i<4; i++)
        {
            temp = new QTableWidgetItem(sql.value(i).toString());
            temp->setFlags(temp->flags() & (~Qt::ItemIsEditable));
            ui->tracksTable->setItem(row,i-1,temp);
        }
        trackIds.append(sql.value(0).toInt());
        row++;
    }
}

void dbBrowser::fillThreadData()
{
    int left = db->left();
    if(left == 0) ui->dbThreadStats->clear();
    else ui->dbThreadStats->setText(QString("%1 left to add").arg(left));
}

void dbBrowser::fillEditableData()
{
    QList<QTableWidgetItem*> selected;

    selected = ui->artistsTable->selectedItems();
    if(!selected.isEmpty())
        ui->artistEdit->setText(selected.first()->text());

    selected = ui->albumsTable->selectedItems();
    if(!selected.isEmpty())
        ui->albumEdit->setText(selected.first()->text());

    selected = ui->tracksTable->selectedItems();
    if(!selected.isEmpty())
        ui->trackEdit->setText(selected.first()->text());
}

void dbBrowser::refreshDb()
{
    fillAlbums();
    fillArtists();
    fillTracks();

//    ui->albumsTable->resizeColumnsToContents();
//    ui->artistsTable->resizeColumnsToContents();
//    ui->tracksTable->resizeColumnsToContents();
}

void dbBrowser::truncateDb()
{
    QMessageBox msgBox;
    msgBox.setText("Уверены, что хотите очистить базу?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        QSqlQuery q("delete from tracks");
        if(q.exec()) {
            ui->tracksTable->setRowCount(0);
        }
        else qDebug() << q.lastError().text();
    }
}

void dbBrowser::removeFile()
{
    if(ui->tracksTable->selectedItems().isEmpty()) return;
    int row = ui->tracksTable->selectedItems().first()->row();

    QMessageBox msgBox;
    msgBox.setText("Удалить этот файл?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        QFile::remove(tracks.at(row));
        removeRecord();
    }
}

void dbBrowser::removeRecord()
{
    if(ui->tracksTable->selectedItems().isEmpty()) return;
    int row = ui->tracksTable->selectedItems().first()->row();

    QSqlQuery q(QString("delete from tracks where path='%1'").arg(tracks.at(row)));
    if(q.exec()) {
        ui->tracksTable->removeRow(row);
        tracks.removeAt(row);
    }
    else qDebug() << q.lastError().text();
}

void dbBrowser::search()
{
    QString query = ui->searchEdit->text();

    ui->searchResult->clear();
    if(query.isEmpty())
    {
        ui->searchResultsWidget->clear();
        return;
    }

    QSqlQuery q;
    ui->searchResultsWidget->clear();

    //поиск по исполнителям
    q.exec(QString("select name from artists where name like '%%1%'").arg(query));
    if(!q.isActive())
    {
        ui->searchResult->setText(q.lastError().text());
        return;
    }
    fillSearchResultsSection("Исполнители", q);

    //поиск по альбомам
    q.exec(QString("select name from albums where name like '%%1%'").arg(query));
    if(!q.isActive())
    {
        ui->searchResult->setText(q.lastError().text());
        return;
    }
    fillSearchResultsSection("Альбомы", q);

    //поиск по песням
    q.exec(QString("select title from tracks where title like '%%1%' or path like '%%1%'").arg(query));
    if(!q.isActive())
    {
        ui->searchResult->setText(q.lastError().text());
        return;
    }
    fillSearchResultsSection("Песни", q);
}

void dbBrowser::showStats()
{
    int songCount=0, albumCount=0, artistCount=0;
    double avgSongCount=0, avgAlbumCount=0, avgSongsInAlbum=0;

    QSqlQuery q;
    q.exec("select count(tracks.id) from tracks");
    if(q.isActive())
    {
        q.next();
        songCount = q.value(0).toInt();
    }
    else qDebug() << q.lastError().text();

    q.exec("select count(albums.id) from albums");
    if(q.isActive())
    {
        q.next();
        albumCount = q.value(0).toInt();
    }

    q.exec("select count(artists.id) from artists");
    if(q.isActive())
    {
        q.next();
        artistCount = q.value(0).toInt();
    }

    q.exec("select avg(tcount) from (select count(id) as tcount from tracks group by artistId)");
    if(q.isActive())
    {
        q.next();
        avgSongCount = q.value(0).toDouble();
    }

    q.exec("select avg(tcount) from (select count(id) as tcount from albums group by artistId)");
    if(q.isActive())
    {
        q.next();
        avgAlbumCount = q.value(0).toDouble();
    }

    q.exec("select avg(tcount) from (select count(id) as tcount from tracks group by albumId)");
    if(q.isActive())
    {
        q.next();
        avgSongsInAlbum = q.value(0).toDouble();
    }

    StatsDialog stats;
    stats.setSongCount(songCount);
    stats.setAlbumCount(albumCount);
    stats.setArtistCount(artistCount);
    stats.setAvgArtistSongCount(avgSongCount);
    stats.setAvgArtistAlbumCount(avgAlbumCount);
    stats.setAvgAlbumSongCount(avgSongsInAlbum);
    stats.exec();
}

void dbBrowser::countTotals()
{
    QSqlQuery sql;
    sql.exec("select count(artists.id) from artists");
    sql.next();
    totalArtists = sql.value(0).toInt();

    sql.exec("select count(albums.id) from albums");
    sql.next();
    totalAlbums = sql.value(0).toInt();

    sql.exec("select count(tracks.id) from tracks");
    sql.next();
    totalTracks = sql.value(0).toInt();
}

void dbBrowser::fillSearchResultsSection(QString title, QSqlQuery q)
{
    QTreeWidgetItem* root=0;
    QTreeWidgetItem* temp=0;

    root = new QTreeWidgetItem(ui->searchResultsWidget);
    int row = 0;
    while (q.next())
    {
        temp = new QTreeWidgetItem(root);
        temp->setText(0, q.value(0).toString());
        row++;
    }
    root->setText(0, title+QString(" (%1)").arg(row));
}
