//
// Created by insane on 14.06.20.
//

#include "ViewWithBackAndSettings.h"

ViewWithBackAndSettings::ViewWithBackAndSettings() {
    setName("backAndSettings");
    setParent("");
}

void ViewWithBackAndSettings::drawSettingsButton() {
    viewSettingsSelected = GuiButton((Rectangle) {592, 8, 200, 100}, "options");
}

std::string ViewWithBackAndSettings::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewSettingsSelected) return getSettings();
    return getName();
}

bool ViewWithBackAndSettings::getViewSettingsSelected() {
    return viewSettingsSelected;
}
