//
// Created by insane on 14.06.20.
//

#include "ViewSettingsWireless.h"

ViewSettingsWireless::ViewSettingsWireless() {
    setName("settings wireless");
    setParent("settings");
}

void ViewSettingsWireless::show(Manager *mgr) {
    drawBackButton();
    viewBluetoothSettingsSelected = GuiButton((Rectangle){8, 8, 200, 100}, "bluetooth");
    viewWifiSettingsSelected = GuiButton((Rectangle){224, 8, 200, 100}, "wifi");
    viewHackRFSettingsSelected = GuiButton((Rectangle){8, 128, 200, 100}, "hackrf");
}

std::string ViewSettingsWireless::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewBluetoothSettingsSelected) return "settings wireless bluetooth";
    else if(viewWifiSettingsSelected) return "settings wireless wifi";
    else if(viewHackRFSettingsSelected) return "settings wireless hackrf";
    else return getName();
}

void ViewSettingsWireless::setValuesFalse() {
    viewBackSelected = false;
}
