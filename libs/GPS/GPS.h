//
// Created by insane on 29.01.19.
//

#ifndef CARPI_GPS_H
#define CARPI_GPS_H


#include <string>
#include <gps.h>
#include <mutex>
#include "../Runnable/Runnable.h"

class Position {
private:
    double longitude;
    double latitude;
    double altitude;
    double speed;
    int satellitesUsed;

public:
    Position();
    explicit Position(gps_data_t* gpsData);

    static Position *calculateDrag(double x, double y, int zoom, Position* cp);

    void setLongitude(double lng);
    void setLatitude(double lat);
    void setAltitude(double alt);
    void setSpeed(double spd);
    void setSatellitesUsed(int su);

    double getLongitude();
    double getLatitude();
    double getAltitude();
    double getSpeed();
    int getSatellitesUsed();
    bool empty();
};

class Positions {
private:
    std::string id;
    std::vector<Position> positions;
public:
    Positions();
    Positions(const std::vector<Position>& positions);
};



class GPS : public Runnable {
private:
    Position* position;
    void setCurrentPosition(gps_data_t* data);

public:
    GPS();
    explicit GPS(Position *defaultPosition);

    void run() override;
    Position* getPosition();
};


#endif //CARPI_GPS_H
