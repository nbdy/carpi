//
// Created by insane on 19.07.20.
//

#ifndef CARPI_QT_ISETTINGS_H
#define CARPI_QT_ISETTINGS_H

#include <QSettings>
#include <QString>
#include <QMetaObject>

#define ORG "eberlein"
#define APP "carpi"

#define REGEX_INTEGER "^[0-9]*$"

class ISettings {
public:
    static QSettings* getSettings();
    static QSettings* getSettings(QObject* parent);

     static QMetaType::Type getProbableType(const QVariant& v);
};


#endif //CARPI_QT_ISETTINGS_H
