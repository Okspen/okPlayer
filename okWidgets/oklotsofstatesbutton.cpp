#include "oklotsofstatesbutton.h"

okLotsOfStatesButton::okLotsOfStatesButton(QWidget *parent) :
    QPushButton(parent)
{
    state = 0;
    labels.clear();
    icons.clear();

    connect(this, SIGNAL(clicked()), this, SLOT(changeState()));
}

void okLotsOfStatesButton::setIcons(QList<QIcon> newIcons)
{
    icons = newIcons;
    if(labels.count() != 0) setIcon(icons.at(0));
}

void okLotsOfStatesButton::setLabels(QList<QString> newLabels)
{
    labels = newLabels;

    if(labels.count() != 0) setText(labels.at(0));
    else setText("No labels");
}

void okLotsOfStatesButton::changeState()
{
    state++;
    if(state>=labels.count()) state = 0;

    if(state>=0 && state<labels.count()) setText(labels.at(state));
    if(state>=0 && state<icons.count()) setIcon(icons.at(state));

    emit stateChanged(state);
}

void okLotsOfStatesButton::setState(int newState)
{
    int max = qMax(labels.count(), icons.count());
    if(newState>=0 && newState<max)
        while(state != newState) changeState();
}
