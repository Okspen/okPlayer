#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include "scanprogressdialog.h"
#include "filesystemmodel.h"
#include "filesystemitemdelegate.h"
//#include "misc/filelistgenerator.h"

namespace Ui {
class FileSystemWidget;
}

class FileSystemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystemWidget(QWidget *parent = 0);
    void cd(const QString &path);
    QString currentPath() const;
    ~FileSystemWidget();

public slots:
    void setFocusOnFilter();

private:
    Ui::FileSystemWidget    *ui;
    FileSystemModel         *m_model;
    QSortFilterProxyModel   *m_sortModel;
    FileSystemItemDelegate  *m_delegate;
    ScanProgressDialog      *m_scanDialog;
    QTimer                  m_scanDialogTimer;

    void initModel();
    void initSearch();

private slots:
    void playAll();
    void playRoot();
    void addAll();
    void addRoot();
    void selectFolder();
    void showScanDialog();
    void onPathChanged();
};

#endif // FILESYSTEMWIDGET_H
