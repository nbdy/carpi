//
// Created by insane on 10.08.20.
//

#ifndef CARPI_QML_UTILS_H
#define CARPI_QML_UTILS_H

#include <QtQml>

#include "CPUTemperature/CPUTemperature.h"
#include "IsFile/IsFile.h"

class Utils {
public:
    static void registerTypes() {
        qmlRegisterType<IsFile>("utils", 1, 0, "IsFile");
        qmlRegisterType<CPUTemperature>("utils", 1, 0, "CPUTemperature");
    }
};

#endif //CARPI_QML_UTILS_H
