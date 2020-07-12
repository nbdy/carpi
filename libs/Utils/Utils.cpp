//
// Created by insane on 11.07.20.
//

#include "Utils.h"

#include <QFile>

bool Utils::isPi() {
    return QFile::exists("/sys/firmware/devicetree/base/model");
}

float Utils::getCPUTemp() {
    if(Utils::isPi()){
        QFile temp("/sys/class/thermal/thermal_zone0/temp");
        temp.open(QFile::ReadOnly);
        return temp.readLine().toFloat() / 1000;
    }
    return -1;
}
