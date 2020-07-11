//
// Created by insane on 14.06.20.
//

#include "ViewWireless.h"

ViewWireless::ViewWireless() {
    setName("wireless");
    setParent("main menu");
}

void ViewWireless::show(Manager *mgr) {
    viewBluetoothSelected = GuiButton((Rectangle) {8, 8, 200, 100}, "bluetooth");
    viewWiFiSelected = GuiButton((Rectangle) {8, 128, 200, 100}, "wifi");
    viewHackRFSelected = GuiButton((Rectangle){224, 8, 200, 100}, "hackrf");
    drawBackButton();
    drawSettingsButton();
}

std::string ViewWireless::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewSettingsSelected) return getSettings();
    else if(viewBluetoothSelected) return "wireless bluetooth";
    else if(viewWiFiSelected) return "wireless wifi";
    else if(viewHackRFSelected) return "wireless hackrf";
    else return getName();
}

void ViewWireless::setValuesFalse() {
    viewBluetoothSelected = false;
    viewWiFiSelected = false;
    viewBackSelected = false;
    viewSettingsSelected = false;
}
