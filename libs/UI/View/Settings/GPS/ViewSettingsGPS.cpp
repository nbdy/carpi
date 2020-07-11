//
// Created by insane on 14.06.20.
//

#include "ViewSettingsGPS.h"

ViewSettingsGPS::ViewSettingsGPS() {
    setName("settings gps");
    setParent("settings");
}

void ViewSettingsGPS::show(Manager *mgr) {
    drawBackButton();
}

void ViewSettingsGPS::setValuesFalse() {
    viewBackSelected = false;
}
