#include "searchwidget.h"
#include "ui_searchwidget.h"

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);

    hideShortcut = new QShortcut(Qt::Key_Escape, this);
    hideShortcut->setContext(Qt::WidgetWithChildrenShortcut);
    connect(hideShortcut, SIGNAL(activated()), this, SLOT(hide()));

    connect(ui->buttonClose,        SIGNAL(clicked()),              this,   SLOT(hide()));
    connect(ui->fieldQuickSearch,   SIGNAL(textChanged(QString)),   this,   SIGNAL(textChanged(QString)));
    connect(ui->fieldQuickSearch,   SIGNAL(textChanged(QString)),   this,   SLOT(stringToRegExp(QString)));
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::clear()
{
    ui->fieldQuickSearch->clear();
}

void SearchWidget::setVisible(bool visible)
{
    if (visible) {
        ui->fieldQuickSearch->setFocus();
    } else {
        ui->fieldQuickSearch->clear();
        ui->fieldQuickSearch->clearFocus();
    }
    QWidget::setVisible(visible);
}

void SearchWidget::setPlaceholderText(const QString &text)
{
    ui->fieldQuickSearch->setPlaceholderText(text);
}


void SearchWidget::stringToRegExp(const QString &query)
{
    emit regExpChanged(QRegExp(query, Qt::CaseInsensitive, QRegExp::FixedString));
}
