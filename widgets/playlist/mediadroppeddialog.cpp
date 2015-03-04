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
