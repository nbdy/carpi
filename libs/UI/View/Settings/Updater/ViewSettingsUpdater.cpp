//
// Created by insane on 14.06.20.
//

#include "ViewSettingsUpdater.h"

ViewSettingsUpdater::ViewSettingsUpdater(KeyboardLayout *keyboard) {
    setName("settings updater");
    setParent("settings");
    setKeyboard(keyboard);
}

void ViewSettingsUpdater::drawUrlTextbox(Manager *mgr) {
    if(projectUrl.empty()) {
        projectUrl = mgr->getConfiguration()->getUpdaterConfiguration().url;
        setKeyboardBuffer(projectUrl);
    }
    if(GuiTextBox((Rectangle) {8, 8, 642, 42}, (char*) getKeyboardBuffer().c_str(), mgr->getConfiguration()->getStyleConfiguration().textSize, showKeyboard)) showKeyboard = true;
    processKeyboard();
}

void ViewSettingsUpdater::show(Manager *mgr) {
    onBootCheckboxChecked = GuiCheckBox((Rectangle){654, 54, 42, 42}, "on boot", onBootCheckboxChecked);
    setProjectUrlSelected = GuiButton((Rectangle){654, 8, 84, 42}, "set");
    drawBackButton();
    drawUrlTextbox(mgr);
    if(setProjectUrlSelected) mgr->getConfiguration()->setProjectUrl(projectUrl);
    if(onBootCheckboxChecked) mgr->getConfiguration()->setOnBootUpdater(onBootCheckboxChecked);
}

void ViewSettingsUpdater::setValuesFalse() {
    viewBackSelected = false;  // todo fix not able to leave
    setProjectUrlSelected = false;
}
