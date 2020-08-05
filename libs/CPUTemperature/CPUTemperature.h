//
// Created by insane on 05.08.20.
//

#ifndef CARPI_QML_CPUTEMPERATURE_H
#define CARPI_QML_CPUTEMPERATURE_H

#include <QObject>
#include <QFile>


// todo thread which reads temperature every x seconds
class CPUTemperature : public QObject {
Q_OBJECT
Q_PROPERTY(double temperature READ getTemperature NOTIFY temperatureChanged)
Q_PROPERTY(int interval READ getInterval WRITE setInterval NOTIFY intervalChanged)
Q_PROPERTY(QString temperatureFile READ getTemperatureFile WRITE setTemperatureFile NOTIFY temperatureFileChanged)

public:
    explicit CPUTemperature(QObject *parent = nullptr);
    ~CPUTemperature() override;

    double getTemperature() const;
    void readTemperature();

    void setInterval(int interval);
    int getInterval() const;

    void setTemperatureFile(const QString& file);
    QString getTemperatureFile() const;

signals:
    void temperatureChanged();
    void intervalChanged();
    void temperatureFileChanged();

private:
    double temperature;
    int interval = 500;
    QString temperatureFile = "/sys/class/thermal/thermal_zone0/temp";
};


#endif //CARPI_QML_CPUTEMPERATURE_H
