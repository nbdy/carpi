//
// Created by insane on 05.08.20.
//

#include "CPUTemperature.h"

CPUTemperature::CPUTemperature(QObject *parent) : QObject(parent) {

}

CPUTemperature::~CPUTemperature() {

}

double CPUTemperature::getTemperature() const {
    return temperature;
}

void CPUTemperature::readTemperature() {
    double r = -1;
    QFile t(temperatureFile);
    if(t.open(QIODevice::ReadOnly | QIODevice::Text)) r = t.readAll().toDouble() / 1000;
    if(temperature != r) emit temperatureChanged();
    temperature = r;
}

void CPUTemperature::setInterval(int interval) {
    this->interval = interval;
    emit intervalChanged();
}

int CPUTemperature::getInterval() const {
    return interval;
}

void CPUTemperature::setTemperatureFile(const QString &file) {
    this->temperatureFile = file;
    emit temperatureFileChanged();
}

QString CPUTemperature::getTemperatureFile() const {
    return this->temperatureFile;
}
