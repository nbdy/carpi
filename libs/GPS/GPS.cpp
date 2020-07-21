//
// Created by insane on 12.07.20.
//

#include "GPS.h"

GPS::GPS(QObject *parent) : QObject(parent) {
    settings = ISettings::getSettings(this);
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if(source) {
        source->setUpdateInterval(settings->value(KEY_GPS_UPDATE_INTERVAL, DEFAULT_GPS_UPDATE_INTERVAL).toInt());
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
