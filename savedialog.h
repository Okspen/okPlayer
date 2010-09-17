#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QValidator>
#include <QDebug>

namespace Ui {
    class savedialog;
}

class savedialog : public QDialog
{
    Q_OBJECT

public:
    explicit savedialog(QWidget *parent = 0);
    ~savedialog();
	QString fileName();

private:
	Ui::savedialog *ui;

private slots:
	void checkIfCanBeSaved();
	void checkIfCanBeSaved(QString text);
};

#endif // SAVEDIALOG_H
