//
// Created by insane on 19.07.20.
//

#ifndef CARPI_QT_SETTINGS_H
#define CARPI_QT_SETTINGS_H

#include <QSettings>
#include <QString>

#define ORG "eberlein"
#define APP "carpi"

// GPS DEFINES
#define KEY_GPS_UPDATE_INTERVAL "updateInterval"
#define DEFAULT_GPS_UPDATE_INTERVAL 420
#define KEY_GPS_OLD_WHEN "oldWhen"
#define DEFAULT_GPS_OLD_WHEN 10

class Settings {
public:
    static QSettings* getSettings();
    static QSettings* getSettings(QObject* parent);
};


#endif //CARPI_QT_SETTINGS_H
