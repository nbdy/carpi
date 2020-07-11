//
// Created by insane on 14.06.20.
//

#include "ViewSettingsMap.h"

ViewSettingsMap::ViewSettingsMap() {
    setName("settings map");
    setParent("settings");
}

void ViewSettingsMap::show(Manager *mgr) {
    drawBackButton();
    viewSettingsMapDownloadSelected = GuiButton((Rectangle) {8, 8, 200, 100}, "download");
    viewCacheSettingsSelected = GuiButton((Rectangle){224, 8, 200, 100}, "cache");
}

std::string ViewSettingsMap::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewSettingsMapDownloadSelected) return "settings map download";
    else if(viewCacheSettingsSelected) return "settings map cache";
    else return getName();
}

void ViewSettingsMap::setValuesFalse() {
    viewBackSelected = false;
    viewCacheSettingsSelected = false;
    viewSettingsMapDownloadSelected = false;
}
