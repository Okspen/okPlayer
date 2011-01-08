#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>

namespace Ui {
    class StatsDialog;
}

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(QWidget *parent = 0);
    ~StatsDialog();

    void setSongCount(int songs);
    void setAlbumCount(int albums);
    void setArtistCount(int artists);

    void setAvgArtistSongCount(double songs);
    void setAvgArtistAlbumCount(double albums);
    void setAvgAlbumSongCount(double songs);

private:
    Ui::StatsDialog *ui;
};

#endif // STATSDIALOG_H
