//
// Created by insane on 14.06.20.
//

#include "ViewSettingsAudioAux.h"

ViewSettingsAudioAux::ViewSettingsAudioAux() {
    setName("settings audio aux");
    setParent("settings audio");
}

void ViewSettingsAudioAux::show(Manager *mgr) {
    drawBackButton();
}

void ViewSettingsAudioAux::setValuesFalse() {
    viewBackSelected = false;
}
