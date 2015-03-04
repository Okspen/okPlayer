#ifndef SCANPROGRESSDIALOG_H
#define SCANPROGRESSDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class ScanProgressDialog;
}

class ScanProgressDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScanProgressDialog(QWidget *parent = 0);
    ~ScanProgressDialog();

signals:
    void cancelled();

public slots:
    void setScanPath(const QString &path);
    void onScanFinished();
    void onScanCancelled();

private slots:
    void disableCancelButton();
    void updateScanPath();

private:
    Ui::ScanProgressDialog *ui;
    QTimer m_closetTimer;
    QTimer m_updateTimer;
    QString m_scanPath;
};

#endif // SCANPROGRESSDIALOG_H
