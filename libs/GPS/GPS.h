//
// Created by insane on 12.07.20.
//

#ifndef CARPI_QT_GPS_H
#define CARPI_QT_GPS_H

#include <QObject>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoPositionInfo>

class GPS : public QObject {
    Q_OBJECT
public:
    explicit GPS(QObject *parent = nullptr);

private:
    QGeoPositionInfoSource *source;

private slots:
    void positionUpdated(const QGeoPositionInfo &info);
};


#endif //CARPI_QT_GPS_H
