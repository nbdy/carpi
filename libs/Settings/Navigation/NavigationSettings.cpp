//
// Created by insane on 17.08.20.
//

#include "NavigationSettings.h"

NavigationSettings::NavigationSettings(QObject *parent) : RSettingsQT(parent) {
    QObject::connect(this, &RedisQT::message, this, &NavigationSettings::messageReceived);
}

NavigationSettings::~NavigationSettings() {

}

bool NavigationSettings::isRouting() const {
    return routing;
}

void NavigationSettings::setRouting(bool value) {
    set(KEY_ROUTING, value);
    emit
}

QGeoCoordinate NavigationSettings::getStart() const {
    return QGeoCoordinate(latitudeStart, longitudeStart);
}

void NavigationSettings::setStart(QGeoCoordinate &coord) {
    setLatitudeStart(coord.latitude());
    setLongitudeStart(coord.longitude());
}

double NavigationSettings::getLatitudeStart() const {
    return latitudeStart;
}

void NavigationSettings::setLatitudeStart(double value) {
    set(KEY_LATITUDE_START, value);
    emit latitudeStartChanged(value);
}

double NavigationSettings::getLongitudeStart() const {
    return longitudeStart;
}

void NavigationSettings::setLongitudeStart(double value) {
    set(KEY_LONGITUDE_START, value);
    emit longitudeStartChanged(value);
}

QGeoCoordinate NavigationSettings::getDestination() const {
    return QGeoCoordinate(latitudeDestination, longitudeDestination);
}

void NavigationSettings::setDestination(QGeoCoordinate &coord) {
    setLatitudeDestination(coord.latitude());
    setLongitudeDestination(coord.longitude());
}

double NavigationSettings::getLatitudeDestination() const {
    return latitudeDestination;
}

void NavigationSettings::setLatitudeDestination(double value) {
    set(KEY_LATITUDE_DESTINATION, value);
    emit latitudeDestinationChanged(value);
}

double NavigationSettings::getLongitudeDestination() const {
    return longitudeDestination;
}

void NavigationSettings::setLongitudeDestination(double value) {
    set(KEY_LONGITUDE_DESTINATION, value);
    emit longitudeDestinationChanged(value);
}

void NavigationSettings::setValues() {
    routing = get(KEY_ROUTING).toBool();
    latitudeStart = get(KEY_LATITUDE_START).toDouble();
    longitudeStart = get(KEY_LONGITUDE_START).toDouble();
    latitudeDestination = get(KEY_LATITUDE_DESTINATION).toDouble();
    longitudeDestination = get(KEY_LONGITUDE_DESTINATION).toDouble();
}

void NavigationSettings::setDefaultValues() {
    set(KEY_ROUTING, false);
    set(KEY_LATITUDE_START, 0);
    set(KEY_LONGITUDE_START, 0);
    set(KEY_LATITUDE_DESTINATION, 0);
    set(KEY_LONGITUDE_DESTINATION, 0);
}

bool NavigationSettings::valuesSet() {
    return exists(KEY_ROUTING) && exists(KEY_LATITUDE_START) && exists(KEY_LONGITUDE_START) &&
           exists(KEY_LATITUDE_DESTINATION) && exists(KEY_LONGITUDE_DESTINATION);
}

void NavigationSettings::messageReceived(const QString &channel, const QString &msg) {
    auto doc = str2doc(msg.toStdString());


}
