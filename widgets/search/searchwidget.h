#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QShortcut>
#include <QDebug>

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT    
public:
    explicit SearchWidget(QWidget *parent = 0);
    ~SearchWidget();

public slots:
    void clear();
    void setVisible(bool visible);
    void setPlaceholderText(const QString &text);

signals:
    void textChanged(QString);
    void regExpChanged(QRegExp);
    
private:
    Ui::SearchWidget *ui;
    QShortcut* hideShortcut;

private slots:
    void stringToRegExp(const QString& query);
};

#endif // SEARCHWIDGET_H
