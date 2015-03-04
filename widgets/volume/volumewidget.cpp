#include "volumewidget.h"
#include "ui_volumewidget.h"

VolumeWidget::VolumeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeWidget)
{
    ui->setupUi(this);

    m_volumeStep = 10;

    ui->volumeSlider->setMinimum(1);
    ui->volumeSlider->setMaximum(100);

    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), ui->volumeButton,  SLOT(adjustIcon(int)));
    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this,              SIGNAL(volumeChanged(int)));
    connect(ui->volumeButton, SIGNAL(muteToggled(bool)), this,              SIGNAL(muteToggled(bool)));
}

VolumeWidget::~VolumeWidget()
{
    delete ui;
}

void VolumeWidget::setVolume(int value)
{
    if (value == ui->volumeSlider->value())
        return;
    ui->volumeSlider->setValue(value);
}

void VolumeWidget::volumeUp()
{
    ui->volumeSlider->setValue(ui->volumeSlider->value() + m_volumeStep);
}

void VolumeWidget::volumeDown()
{
    ui->volumeSlider->setValue(ui->volumeSlider->value() - m_volumeStep);
}

void VolumeWidget::setMute(bool mute)
{
    ui->volumeButton->setMute(mute);
}
