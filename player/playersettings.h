#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

class PlayerSettings : public QSettings
{
public:
    static QString     dataLocation();
    static QStringList nameFilters();

private:
    static QStringList m_dataLocation;
};

#endif // PLAYERSETTINGS_H
