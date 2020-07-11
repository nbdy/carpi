//
// Created by insane on 14.06.20.
//

#include "ViewSettingsWirelessBluetooth.h"

ViewSettingsWirelessBluetooth::ViewSettingsWirelessBluetooth() {
    setName("settings wireless bluetooth");
    setParent("settings wireless");
}

void ViewSettingsWirelessBluetooth::show(Manager *mgr) {
    drawBackButton();
}

void ViewSettingsWirelessBluetooth::setValuesFalse() {
    viewBackSelected = false;
}
