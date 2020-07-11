//
// Created by insane on 14.06.20.
//

#include "ViewWirelessWiFi.h"

ViewWirelessWiFi::ViewWirelessWiFi() {
    setName("wireless wifi");
    setParent("wireless");
    interfaceList = Network::getWiFiInterfaces();
    joinedInterfaceList = Utils::joinList(interfaceList, ";");
}

void ViewWirelessWiFi::drawPromiscuousCheckbox() {
    promiscuousCheckboxChecked = GuiCheckBox((Rectangle){332, 8, 42, 42}, "promisc", promiscuousCheckboxChecked);
}

void ViewWirelessWiFi::scan(Manager *mgr) {
    if(scanButtonSelected) {
        // todo
    }
}

void ViewWirelessWiFi::show(Manager *mgr) {
    drawBackButton();
    drawSettingsButton();
    drawScanButton();
    scan(mgr);
    drawPromiscuousCheckbox();
    drawScanningInformation();
    drawInterfaceList(mgr);
    drawFoundDevices();
    _drawBaseUI();
}

void ViewWirelessWiFi::setValuesFalse() {
    viewBackSelected = false;
    viewSettingsSelected = false;
}
