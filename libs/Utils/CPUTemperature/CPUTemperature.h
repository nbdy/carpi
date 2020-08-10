//
// Created by insane on 05.08.20.
//

#ifndef CARPI_QML_CPUTEMPERATURE_H
#define CARPI_QML_CPUTEMPERATURE_H

#include <thread>
#include <atomic>

#include <QObject>
#include <QFile>


// todo thread which reads temperature every x seconds
class CPUTemperature : public QObject {
Q_OBJECT
Q_PROPERTY(double temperature READ getTemperature NOTIFY temperatureChanged)
Q_PROPERTY(int interval READ getInterval WRITE setInterval NOTIFY intervalChanged)
Q_PROPERTY(QString temperatureFile READ getTemperatureFile WRITE setTemperatureFile NOTIFY temperatureFileChanged)
Q_PROPERTY(bool doRead READ getDoRead WRITE setDoRead NOTIFY doReadChanged)

public:
    explicit CPUTemperature(QObject *parent = nullptr);
    ~CPUTemperature() override;

    double getTemperature() const;
    void readTemperature();

    void setInterval(int interval);
    int getInterval() const;

    void setTemperatureFile(const QString& file);
    QString getTemperatureFile() const;

    void setDoRead(bool value);
    bool getDoRead() const;

signals:
    void temperatureChanged();
    void intervalChanged();
    void temperatureFileChanged();
    void doReadChanged();

private:
    void readLoop();

    std::thread readThread;

    std::atomic<bool> doRead = true;
    double temperature;
    int interval = 500;
    QString temperatureFile = "/sys/class/thermal/thermal_zone0/temp";
};


#endif //CARPI_QML_CPUTEMPERATURE_H
