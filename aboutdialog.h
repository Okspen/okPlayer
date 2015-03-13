#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QFont>
#include <QFile>
#include <QDate>
#include <QUrl>
#include <QDesktopServices>
#include <QDebug>

namespace Ui {
    class aboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::aboutDialog *ui;
};

#endif // ABOUTDIALOG_H
