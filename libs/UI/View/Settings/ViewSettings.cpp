//
// Created by insane on 14.06.20.
//

#include "ViewSettings.h"

ViewSettings::ViewSettings() {
    setName("settings");
    setParent("main menu");
}

void ViewSettings::show(Manager *mgr) {
    viewGPSSettingsSelected = GuiButton((Rectangle) {8, 8, 200, 100}, "gps");
    viewWirelessSettingsSelected = GuiButton((Rectangle) {8, 128, 200, 100}, "wireless");
    viewAudioSettingsSelected = GuiButton((Rectangle) {224, 8, 200, 100}, "audio");
    viewMapSettingsSelected = GuiButton((Rectangle) {224, 128, 200, 100}, "map");
    viewUpdaterSettingsSelected = GuiButton((Rectangle){8, 248, 200, 100}, "updater");
    viewSystemSettingsSelected = GuiButton((Rectangle){224, 248, 200, 100}, "system");
    drawBackButton();
}

std::string ViewSettings::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewGPSSettingsSelected) return "settings gps";
    else if(viewWirelessSettingsSelected) return "settings wireless";
    else if(viewAudioSettingsSelected) return "settings audio";
    else if(viewMapSettingsSelected) return "settings map";
    else if(viewUpdaterSettingsSelected) return "settings updater";
    else if(viewSystemSettingsSelected) return "settings system";
    else return getName();
}

void ViewSettings::setValuesFalse() {
    viewGPSSettingsSelected = false;
    viewWirelessSettingsSelected = false;
    viewAudioSettingsSelected = false;
    viewBackSelected = false;
    viewMapSettingsSelected = false;
    viewUpdaterSettingsSelected = false;
    viewSystemSettingsSelected = false;
}
