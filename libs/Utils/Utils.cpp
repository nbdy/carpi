//
// Created by insane on 11.07.20.
//

#include "Utils.h"

#include <QFile>

bool Utils::isPi() {
    return QFile::exists("/sys/firmware/devicetree/base/model");
}
