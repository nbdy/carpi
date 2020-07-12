//
// Created by insane on 12.07.20.
//

#include "GPS.h"

GPS::GPS(QObject *parent) : QObject(parent) {
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if(source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();
    } else {
        // todo inform that no source available since there is probably no adapter connected
    }
}

void GPS::positionUpdated(const QGeoPositionInfo &info) {
    // todo
}
