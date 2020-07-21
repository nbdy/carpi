//
// Created by insane on 12.07.20.
//

#include "GPS.h"

GPS::GPS(QObject *parent) : QObject(parent) {
    settings = ISettings::getSettings(this);
    setDefaultSettings();
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if(source) {
        source->setUpdateInterval(settings->value(KEY_UPDATE_INTERVAL).toInt());
        connect(source, &QGeoPositionInfoSource::positionUpdated, this, &GPS::positionUpdated);
        connect(source, &QGeoPositionInfoSource::updateTimeout, this, &GPS::updateTimeout);
        source->startUpdates();
    } else qDebug() << "could not create gps source";
}

void GPS::positionUpdated(const QGeoPositionInfo &info) {
    if(lastInfo.coordinate() != info.coordinate()){
        lastInfo = info;
        emit positionChanged(info);
    }
}

void GPS::updateTimeout() {
    qDebug() << "gps update timeout";
    emit positionOld(lastInfo.timestamp());
}

void GPS::setDefaultSettings() {
    if(settings->contains(KEY_GROUP_GPS)) return;
    settings->beginGroup(KEY_GROUP_GPS);
    settings->setValue(KEY_UPDATE_INTERVAL, 420);
    settings->endGroup();
}

GPS::~GPS() {
    settings->sync();
    source->stopUpdates();
    delete settings;
    delete source;
}
