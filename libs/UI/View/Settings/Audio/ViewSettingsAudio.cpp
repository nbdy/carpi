//
// Created by insane on 14.06.20.
//

#include "ViewSettingsAudio.h"

ViewSettingsAudio::ViewSettingsAudio() {
    setName("settings audio");
    setParent("settings");
    setKeyboard(new KeyboardLayout());
}

void ViewSettingsAudio::show(Manager *mgr) {
    drawBackButton();
    viewAudioAuxSettings = GuiButton((Rectangle){8, 8, 200, 100}, "aux");
    viewAudioRadioSettings = GuiButton((Rectangle){224, 8, 200, 100}, "radio");
}

std::string ViewSettingsAudio::getNextView() {
    if(viewBackSelected) return getParent();
    else if(viewAudioRadioSettings) return "settings audio radio";
    else if(viewAudioAuxSettings) return "settings audio aux";
    else return getName();
}

void ViewSettingsAudio::setValuesFalse() {
    viewBackSelected = false;
    viewAudioRadioSettings = false;
    viewAudioAuxSettings = false;
}
