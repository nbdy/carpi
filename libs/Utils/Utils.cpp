//
// Created by insane on 11.07.20.
//

#include "Utils.h"

#include <QFile>

bool Utils::isPi() {
    return QFile::exists("/sys/firmware/devicetree/base/model");
}

float Utils::getCPUTemp() {
    if(Utils::isPi() || Utils::isCPUIntel()){
        QFile t("/sys/class/thermal/thermal_zone0/temp");
        if(t.open(QIODevice::ReadOnly | QIODevice::Text)) return t.readAll().toFloat() / 1000;
    }
    return -1;
}

bool Utils::isCPUIntel() {
    QFile t("/proc/cpuinfo");
    if(t.open(QIODevice::ReadOnly | QIODevice::Text)) return t.readAll().contains("Intel");
    return false;
}
