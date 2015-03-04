#include "scanprogressdialog.h"
#include "ui_scanprogressdialog.h"

ScanProgressDialog::ScanProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanProgressDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowCloseButtonHint);

    m_closetTimer.setSingleShot(true);
    connect(&m_closetTimer, SIGNAL(timeout()), this, SLOT(close()));

    m_updateTimer.setInterval(200);
    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(updateScanPath()));
    m_updateTimer.start();

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(disableCancelButton()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SIGNAL(cancelled()));
}

ScanProgressDialog::~ScanProgressDialog()
{
    delete ui;
}

void ScanProgressDialog::setScanPath(const QString &path)
{
    m_scanPath = path;
}

void ScanProgressDialog::onScanFinished()
{
    m_scanPath.clear();
    ui->label->setText("Done");
    m_closetTimer.start(1000);
}

void ScanProgressDialog::onScanCancelled()
{
    m_scanPath.clear();
    ui->label->setText("Cancelled");
    ui->cancelButton->setEnabled(true);
    m_closetTimer.start(1000);
}

void ScanProgressDialog::disableCancelButton()
{
    ui->cancelButton->setEnabled(false);
}

void ScanProgressDialog::updateScanPath()
{
    if (m_scanPath.isEmpty())
        return;

    QFontMetrics fm = ui->label->fontMetrics();
    int scanningWidth   = fm.width("Scanning: ");
    QString elidedPath  = fm.elidedText(m_scanPath, Qt::ElideMiddle, ui->label->width() - scanningWidth);
    ui->label->setText("Scanning: " + elidedPath);
}
