#include "statsdialog.h"
#include "ui_statsdialog.h"

StatsDialog::StatsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));
}

StatsDialog::~StatsDialog()
{
    delete ui;
}

void StatsDialog::setSongCount(int songs)
{
    ui->songCount->setText(QString("%1").arg(songs));
}

void StatsDialog::setAlbumCount(int albums)
{
    ui->albumCount->setText(QString("%1").arg(albums));
}

void StatsDialog::setArtistCount(int artists)
{
    ui->artistCount->setText(QString("%1").arg(artists));
}

void StatsDialog::setAvgArtistSongCount(double songs)
{
    ui->avgSongCount->setText(QString("%1").arg(songs));
}

void StatsDialog::setAvgArtistAlbumCount(double albums)
{
    ui->avgAlbumCount->setText(QString("%1").arg(albums));
}

void StatsDialog::setAvgAlbumSongCount(double songs)
{
    ui->avgAlbumSongCount->setText(QString("%1").arg(songs));
}
