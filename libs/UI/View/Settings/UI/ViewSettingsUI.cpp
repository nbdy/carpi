//
// Created by insane on 14.06.20.
//

#include "ViewSettingsUI.h"

ViewSettingsUI::ViewSettingsUI() {
    setName("settings ui");
    setParent("settings");
}

void ViewSettingsUI::show(Manager *mgr) {
    drawBackButton();
    // todo color / design chooser
}

void ViewSettingsUI::setValuesFalse() {
    viewBackSelected = false;
}
