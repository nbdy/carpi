//
// Created by insane on 14.06.20.
//

#include "ViewAudio.h"

ViewAudio::ViewAudio() {
    setName("audio");
    setParent("main menu");
}

void ViewAudio::show(Manager *mgr) {
    viewAudioAuxSelected = GuiButton((Rectangle) {8, 8, 200, 100}, "aux");
    viewAudioRadioSelected = GuiButton((Rectangle) {8, 128, 200, 100}, "radio");
    drawBackButton();
    drawSettingsButton();
}

std::string ViewAudio::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewSettingsSelected) return getSettings();
    else if(viewAudioAuxSelected) return "audio aux";
    else if(viewAudioRadioSelected) return "audio radio";
    else return getName();
}

void ViewAudio::setValuesFalse() {
    viewAudioAuxSelected = false;
    viewAudioRadioSelected = false;
    viewBackSelected = false;
    viewSettingsSelected = false;
}
