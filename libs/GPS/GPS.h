//
// Created by insane on 12.07.20.
//

#ifndef CARPI_QT_GPS_H
#define CARPI_QT_GPS_H

#include "../ISettings/ISettings.h"

#include <QDebug>
#include <QSettings>
#include <QTimer>
#include <QObject>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoPositionInfo>

class GPS : public QObject {
    Q_OBJECT
public:
    explicit GPS(QObject *parent = nullptr);

private:
    QSettings *settings;
    QGeoPositionInfoSource *source;
    QGeoPositionInfo lastInfo;

private slots:
    void updateTimeout();
    void positionUpdated(const QGeoPositionInfo &info);

signals:
    void positionChanged(const QGeoPositionInfo &info);
    void positionOld(const QDateTime &ts);
};


#endif //CARPI_QT_GPS_H
