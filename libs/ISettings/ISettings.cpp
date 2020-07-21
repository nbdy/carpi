//
// Created by insane on 19.07.20.
//

#include "ISettings.h"

QSettings* ISettings::getSettings() {
    return new QSettings(ORG, APP);
}

QSettings *ISettings::getSettings(QObject *parent) {
    return new QSettings(ORG, APP, parent);
}
