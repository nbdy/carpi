//
// Created by insane on 19.07.20.
//

#include "Settings.h"

QSettings* Settings::getSettings() {
    return new QSettings(ORG, APP);
}

QSettings *Settings::getSettings(QObject *parent) {
    return new QSettings(ORG, APP, parent);
}
