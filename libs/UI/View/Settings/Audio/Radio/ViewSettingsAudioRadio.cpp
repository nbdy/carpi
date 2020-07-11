//
// Created by insane on 14.06.20.
//

#include "ViewSettingsAudioRadio.h"

ViewSettingsAudioRadio::ViewSettingsAudioRadio() {
    setName("settings audio radio");
    setParent("settings audio");
}

void ViewSettingsAudioRadio::show(Manager *mgr) {
    drawBackButton();
    frequencySliderValue = GuiSlider((Rectangle){64, 8, 400, 50}, "freq", TextFormat("%2.2f", 94.2), 80, 110, true);
}

void ViewSettingsAudioRadio::setValuesFalse() {
    viewBackSelected = false;
}

float ViewSettingsAudioRadio::getFrequencySliderValue() {
    return frequencySliderValue;
}
