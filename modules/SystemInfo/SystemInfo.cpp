//
// Created by insane on 11.07.20.
//

#include "SystemInfo.h"

extern "C" SYSTEMINFO_EXPORT QWidget* render() {
    auto *w = new QWidget();

    return w;
}

extern "C" SYSTEMINFO_EXPORT QString getName() {
    return "SystemInfo";
}



