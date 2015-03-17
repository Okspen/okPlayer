#ifndef MEDIADROPPEDDIALOG_H
#define MEDIADROPPEDDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include "player/player.h"

namespace Ui {
class MediaDroppedDialog;
}

class MediaDroppedDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MediaDroppedDialog(QWidget *parent = 0);
    ~MediaDroppedDialog();
    bool toAppend() const;
    bool toNew() const;
    bool root() const;

    void setFileFolderCount(int fileCount, int folderCount);
    
private:
    Ui::MediaDroppedDialog *ui;
    bool m_append;

private slots:
    void processButtonClick(QAbstractButton *button);
};

#endif // MEDIADROPPEDDIALOG_H
