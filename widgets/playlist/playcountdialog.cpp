#include "playcountdialog.h"
#include "ui_playcountdialog.h"

PlayCountDialog::PlayCountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayCountDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui->setButton, SIGNAL(clicked()), this, SLOT(accept()));

    setFixedSize(width(), height());
}

PlayCountDialog::~PlayCountDialog()
{
    delete ui;
}

int PlayCountDialog::playCount() const
{
    return ui->spinBox->value();
}

void PlayCountDialog::setPlayCount(int count)
{
    setResult(1);
    return ui->spinBox->setValue(count);
}
