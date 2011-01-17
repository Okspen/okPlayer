#ifndef OKPLAYPAUSEBUTTON_H
#define OKPLAYPAUSEBUTTON_H

#include <QToolButton>
#include <QStateMachine>

class okPlayPauseButton : public QToolButton
{
    Q_OBJECT
public:
    explicit okPlayPauseButton(QWidget *parent = 0);
    ~okPlayPauseButton();
    QState* play;
    QState* pause;

signals:

public slots:

private:
    QStateMachine machine;

};

#endif // OKPLAYPAUSEBUTTON_H
