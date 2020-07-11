//
// Created by insane on 29.01.19.
//

#include <libgpsmm.h>
#include <iostream>
#include <gps.h>
#include "GPS.h"
#include "../Navigation/Navigation.h"

GPS::GPS() {
    position = new Position();
    setName("GPS");
    setDoRun(true);
}

GPS::GPS(Position *defaultPosition) {
    position = defaultPosition;
    setName("GPS");
    setDoRun(true);
}

void GPS::run() {
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
    if(gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == nullptr) this->setDoRun(false);
    while (this->getDoRun()) {
        struct gps_data_t* nd;
        if(!gps_rec.waiting(5000000)) {} // timeout after 5 seconds
        if((nd = gps_rec.read()) == nullptr) continue;
        else setCurrentPosition(nd);
    }
}

void GPS::setCurrentPosition(gps_data_t* data) {
    if(data->satellites_used >= 3) position = new Position(data);
}

Position::Position(gps_data_t* gpsData) {
    longitude = gpsData->fix.longitude;
    latitude = gpsData->fix.latitude;
    altitude = gpsData->fix.altitude;
    speed = gpsData->fix.speed;
    satellitesUsed = gpsData->satellites_used;
}

Position::Position() {
    longitude = 0;
    latitude = 0;
    altitude = 0;
    speed = 0;
    satellitesUsed = 0;
}

Position* GPS::getPosition() {return position;}

double Position::getAltitude() { return altitude;}

double Position::getLongitude() {return longitude;}

double Position::getLatitude() {return latitude;}

int Position::getSatellitesUsed() {return satellitesUsed;}

double Position::getSpeed() {return speed;}

bool Position::empty() {
    return satellitesUsed == 0;
}

void Position::setSatellitesUsed(int su) {
    this->satellitesUsed = su;
}

void Position::setSpeed(double spd) {
    this->speed = spd;
}

void Position::setAltitude(double alt) {
    this->altitude = alt;
}

void Position::setLatitude(double lat) {
    this->latitude = lat;
}

void Position::setLongitude(double lng) {
    this->longitude = lng;
}

Position* Position::calculateDrag(double x, double y, int zoom, Position *cp) {
    auto *p = new Position();
    p->longitude = Navigation::tilex2long(x, zoom);
    p->latitude = Navigation::tiley2lat(y, zoom);
    p->altitude = cp->altitude;
    p->speed = 0;
    p->satellitesUsed = 420;
    return p;
}

Positions::Positions() {}

Positions::Positions(const std::vector<Position> &positions) {
    this->positions = positions;
}