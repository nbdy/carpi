//
// Created by insane on 06.08.20.
//

#include "AsyncSettings.h"

AsyncSettings::AsyncSettings(QObject *parent) : QObject(parent) {
    _createSettings();
}

AsyncSettings::~AsyncSettings() {
    settings->sync();
    delete settings;
}

void AsyncSettings::setValue(const QString &key, const QVariant &value) {
    if(!group.isEmpty()) settings->beginGroup(group);
    settings->setValue(key, value);
    if(!group.isEmpty()) settings->endGroup();
    settings->sync();
    emit valueChanged(key, value);
}

QVariant AsyncSettings::getValue(const QString &key) const {
    QVariant r;
    if(!group.isEmpty()) settings->beginGroup(group);
    r = settings->value(key);
    if(!group.isEmpty()) settings->endGroup();
    return r;
}

void AsyncSettings::setOrganizationName(const QString &name) {
    organizationName = name;
    emit organizationNameChanged();
    _createSettings();
}

void AsyncSettings::_createSettings() {
    if(settings != nullptr) {
        settings->sync();
        delete settings;
    }
    settings = new QSettings(organizationName, applicationName);
    emit settingsReady();
}

QString AsyncSettings::getOrganizationName() const {
    return organizationName;
}

void AsyncSettings::setApplicationName(const QString &name) {
    applicationName = name;
    emit applicationNameChanged();
    _createSettings();
}

QString AsyncSettings::getApplicationName() const {
    return applicationName;
}

void AsyncSettings::setGroup(const QString &group) {
    this->group = group;
    emit groupChanged();
}

QString AsyncSettings::getGroup() const {
    return group;
}
