//
// Created by insane on 17.08.20.
//

#ifndef CARPI_QML_NAVIGATIONSETTINGS_H
#define CARPI_QML_NAVIGATIONSETTINGS_H

#include <QtPositioning>

#include <rsettingsqt/rsettingsqt.h>

#define KEY_SETTINGS_NAVIGATION "navigation/"
#define KEY_ROUTING "routing"
#define KEY_LATITUDE_START "latitudeStart"
#define KEY_LONGITUDE_START "longitudeStart"
#define KEY_LATITUDE_DESTINATION "latitudeDestination"
#define KEY_LONGITUDE_DESTINATION "longitudeDestination"

class NavigationSettings : public RSettingsQT {
    Q_OBJECT
    Q_PROPERTY(bool routing READ isRouting WRITE setRouting NOTIFY routingChanged)
    Q_PROPERTY(double latitudeStart READ getLatitudeStart WRITE setLatitudeStart NOTIFY latitudeStartChanged)
    Q_PROPERTY(double longitudeStart READ getLongitudeStart WRITE setLongitudeStart NOTIFY longitudeStartChanged)
    Q_PROPERTY(double latitudeDestination READ getLatitudeDestination WRITE setLatitudeDestination NOTIFY latitudeDestinationChanged)
    Q_PROPERTY(double longitudeDestination READ getLongitudeDestination WRITE setLongitudeDestination NOTIFY longitudeDestinationChanged)
    Q_PROPERTY(QGeoCoordinate start READ getStart WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(QGeoCoordinate destination READ getDestination WRITE setDestination NOTIFY destinationChanged)

public:
    explicit NavigationSettings(QObject *parent = nullptr);
    ~NavigationSettings() override;

    static void registerType();

    [[nodiscard]] bool isRouting() const;
    void setRouting(bool value);

    [[nodiscard]] QGeoCoordinate getStart() const;
    void setStart(QGeoCoordinate& coord);
    [[nodiscard]] double getLatitudeStart() const;
    void setLatitudeStart(double value);
    [[nodiscard]] double getLongitudeStart() const;
    void setLongitudeStart(double value);

    [[nodiscard]] QGeoCoordinate getDestination() const;
    void setDestination(QGeoCoordinate& coord);
    [[nodiscard]] double getLatitudeDestination() const;
    void setLatitudeDestination(double value);
    [[nodiscard]] double getLongitudeDestination() const;
    void setLongitudeDestination(double value);

    void setValues() override;
    void setDefaultValues() override;
    bool valuesSet() override;

public slots:
    void messageReceived(const QString& channel, const QString& msg);

signals:
    void routingChanged(bool value);
    void startChanged(const QGeoCoordinate& coordinate);
    void latitudeStartChanged(double value);
    void longitudeStartChanged(double value);
    void destinationChanged(const QGeoCoordinate& coordinate);
    void latitudeDestinationChanged(double value);
    void longitudeDestinationChanged(double value);


private:
    bool routing;

    double latitudeStart;
    double longitudeStart;

    double latitudeDestination;
    double longitudeDestination;
};


#endif //CARPI_QML_NAVIGATIONSETTINGS_H
