//
// Created by insane on 14.06.20.
//

#include "ViewSettingsWirelessHackRF.h"

ViewSettingsWirelessHackRF::ViewSettingsWirelessHackRF() {
    setName("settings wireless hackrf");
    setParent("settings wireless");
}

void ViewSettingsWirelessHackRF::show(Manager *mgr) {
    drawBackButton();
}
