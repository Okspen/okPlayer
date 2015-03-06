#ifndef PLAYCOUNTDIALOG_H
#define PLAYCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class PlayCountDialog;
}

class PlayCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayCountDialog(QWidget *parent = 0);
    ~PlayCountDialog();

    int playCount() const;
    void setPlayCount(int count);

private:
    Ui::PlayCountDialog *ui;
};

#endif // PLAYCOUNTDIALOG_H
