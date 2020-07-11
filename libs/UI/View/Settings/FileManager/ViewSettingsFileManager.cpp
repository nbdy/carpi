//
// Created by insane on 14.06.20.
//

#include "ViewSettingsFileManager.h"

ViewSettingsFileManager::ViewSettingsFileManager() {
    setParent("settings");
    setName("settings file manager");
}

void ViewSettingsFileManager::show(Manager *mgr) {
    drawBackButton();
}

void ViewSettingsFileManager::setValuesFalse() {
    viewBackSelected = false;
}
