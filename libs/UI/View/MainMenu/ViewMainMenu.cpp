//
// Created by insane on 14.06.20.
//

#include "ViewMainMenu.h"

ViewMainMenu::ViewMainMenu() {
    setName("main menu");
    setParent("main");
}

void ViewMainMenu::show(Manager *mgr) {
    drawBackButton();
    drawSettingsButton();
    viewAudioSelected = GuiButton((Rectangle) {8, 8, 200, 100}, "audio");
    viewWirelessSelected = GuiButton((Rectangle) {224, 8, 200, 100}, "wireless");
    viewMapSelected = GuiButton((Rectangle) {8, 128, 200, 100}, "map");
    viewFileManagerSelected = GuiButton((Rectangle) {224, 128, 200, 100}, "file manager");
    viewUpdaterSelected = GuiButton((Rectangle) {8, 248, 200, 100}, "updater");
}

std::string ViewMainMenu::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewAudioSelected) return "audio";
    else if(viewWirelessSelected) return "wireless";
    else if(viewSettingsSelected) return "settings";
    else if(viewMapSelected) return "map";
    else if(viewFileManagerSelected) {
        addToast(new Toast("under construction", 3));
        return getName();
    }
    else if(viewUpdaterSelected) return "updater";
    else return getName();
}

void ViewMainMenu::setValuesFalse() {
    viewBackSelected = false;
    viewAudioSelected = false;
    viewWirelessSelected = false;
    viewSettingsSelected = false;
    viewMapSelected = false;
    viewFileManagerSelected = false;
    viewUpdaterSelected = false;
}
