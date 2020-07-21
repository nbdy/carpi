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

QMetaType::Type ISettings::getProbableType(const QVariant &v) {
    auto s = v.toString();
    if(s == "true" || s == "false") return QMetaType::Bool;
    else if(s.contains(QRegExp(REGEX_INTEGER))) return QMetaType::Int;
    else return QMetaType::QString;
}
