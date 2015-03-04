#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));

    QFont f1("Tahoma"), f2("Tahoma");
    f1.setPointSize(20);
    f2.setPointSize(10);

    ui->label->setFont(f1);
    ui->label->setText(QCoreApplication::applicationName());

    ui->versionLabel->setFont(f2);
    ui->versionLabel->setText(QCoreApplication::applicationVersion());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::sendEmail(const QString &email)
{
    QDesktopServices::openUrl(email);
}
