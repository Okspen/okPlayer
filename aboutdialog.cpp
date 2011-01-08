#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "vlc/vlc.h"

aboutDialog::aboutDialog(QWidget *parent) :
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

    ui->label_4->setFont(f2);
    ui->label_4->setText(QCoreApplication::applicationVersion());

    ui->libvlcLabel->setText(libvlc_get_version());

    readChangelog();
}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::readChangelog()
{
    QFile changelog(QCoreApplication::applicationDirPath()+"/changelog.txt");
    if(!changelog.open(QFile::ReadOnly)) return;

    ui->changelogText->setPlainText(changelog.readAll());

    changelog.close();
}
