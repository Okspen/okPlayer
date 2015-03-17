#include "mediadroppeddialog.h"
#include "ui_mediadroppeddialog.h"

MediaDroppedDialog::MediaDroppedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MediaDroppedDialog)
{
    ui->setupUi(this);

    m_append = false;
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(processButtonClick(QAbstractButton*)));

    setFixedSize(width(), height());
}

MediaDroppedDialog::~MediaDroppedDialog()
{
    delete ui;
}

void MediaDroppedDialog::processButtonClick(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole buttonRole = ui->buttonBox->buttonRole(button);

    if (buttonRole == QDialogButtonBox::AcceptRole) {
        if (ui->radioAppend->isChecked())
            m_append = true;
        if (ui->radioReplace->isChecked())
            m_append = false;

        done(1);
    } else {
        done(0);
    }
}

bool MediaDroppedDialog::toAppend() const
{
    return m_append;
}

bool MediaDroppedDialog::toNew() const
{
    return !m_append;
}

bool MediaDroppedDialog::root() const
{
    return ui->rootCheckBox->isChecked();
}

void MediaDroppedDialog::setFileFolderCount(int fileCount, int folderCount)
{
    QString fileString;
    QString folderString;

    if (fileCount == 1)
        fileString = QString("%1 file").arg(fileCount);
    if (fileCount > 1)
        fileString = QString("%1 files").arg(fileCount);

    if (folderCount == 1)
        folderString = QString("%1 folder").arg(folderCount);
    if (folderCount > 1)
        folderString = QString("%1 folders").arg(folderCount);

    QString labelText = "You have dropped";
    if (folderCount > 0)
        labelText += " " + folderString;
    if (folderCount > 0 && fileCount > 0)
        labelText += " and";
    if (fileCount > 0)
        labelText += " " + fileString;

    labelText += ".";

    labelText += "\nWhat do you want to do?";

    ui->label->setText(labelText);
}
