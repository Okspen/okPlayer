#ifndef OKTRISTATEBUTTON_H
#define OKTRISTATEBUTTON_H

#include <QPushButton>
#include <QDebug>

class okLotsOfStatesButton : public QPushButton
{
    Q_OBJECT
public:
    explicit okLotsOfStatesButton(QWidget *parent = 0);
    void setIcons(QList<QIcon> newIcons);
    void setLabels(QList<QString> newLabels);
	void setState(int newState);

signals:
    void stateChanged(int);

public slots:
    void changeState();

private:
    QList<QIcon> icons;
    QList<QString> labels;
    int state;
};

#endif // OKTRISTATEBUTTON_H
