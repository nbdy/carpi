//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_SYSTEMINFO_H
#define CARPI_QT_SYSTEMINFO_H

#include "SystemInfo_global.h"
#include <QWidget>

extern "C" {
    SYSTEMINFO_EXPORT QString getName();
    SYSTEMINFO_EXPORT QWidget* render();
};


#endif //CARPI_QT_SYSTEMINFO_H
