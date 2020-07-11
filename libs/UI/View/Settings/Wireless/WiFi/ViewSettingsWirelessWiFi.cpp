//
// Created by insane on 14.06.20.
//

#include "ViewSettingsWirelessWiFi.h"

ViewSettingsWirelessWiFi::ViewSettingsWirelessWiFi() {
    setName("settings wireless wifi");
    setParent("settings wireless");
}

void ViewSettingsWirelessWiFi::show(Manager *mgr) {
    if(interfaces.empty()) {mgr->getConfiguration()->getWirelessConfiguration().interfaces; joinedInterfaces = Utils::joinList(interfaces, ";").c_str();}
    drawBackButton();
    GuiLabel((Rectangle){8, 8, 42, 100}, "ifaces:");
    if(GuiListView((Rectangle) {100, 200, 100, 342}, joinedInterfaces, &interfacesListViewIndex, interfacesListViewActive))
        interfacesListViewEditMode = !interfacesListViewEditMode;
}

void ViewSettingsWirelessWiFi::setValuesFalse() {
    viewBackSelected = false;
}
