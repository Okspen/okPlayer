#include "playersettings.h"

QStringList PlayerSettings::m_dataLocation = QStringList()
    << "*.wav"
    << "*.mp3"
    << "*.ogg"
    << "*.flac"
    << "*.wma"
    << "*.aac"
    << "*.ac3"
    << "*.ape"
    << "*.alac";

QString PlayerSettings::dataLocation()
{
    QString location =
        QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(location);
    if (!dir.isReadable() || !dir.exists())
        dir.mkpath(location);

    return location;
}

QStringList PlayerSettings::nameFilters()
{
    return PlayerSettings::m_dataLocation;
}
