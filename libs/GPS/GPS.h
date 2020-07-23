//
// Created by insane on 12.07.20.
//

#ifndef CARPI_QT_GPS_H
#define CARPI_QT_GPS_H

#include "../ISettings/ISettings.h"
#include "../Logger/Logger.h"

#include <QSettings>
#include <QTimer>
#include <QObject>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoPositionInfo>

#define KEY_GROUP_GPS "GPS"
#define KEY_UPDATE_INTERVAL "updateInterval"

class GPS : public QObject {
    Q_OBJECT
public:
    explicit GPS(QObject *parent = nullptr);
    ~GPS() override;

private:
    void setDefaultSettings();

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
