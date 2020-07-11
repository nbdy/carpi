//
// Created by insane on 14.06.20.
//

#include "ViewMusicPlayer.h"

ViewMusicPlayer::ViewMusicPlayer() {
    setName("music player");
    setParent("");
}

void ViewMusicPlayer::show(Manager *mgr) {
    _overrideCatchAll();
}

void ViewMusicPlayer::drawBaseUI() {
    _drawBaseUI();
    playPauseButtonSelected = GuiButton((Rectangle){8, 300, 200, 100}, playPauseButtonText.c_str());
    nextButtonSelected = GuiButton((Rectangle){224, 300, 200, 100}, ">>");
    drawSettingsButton();
    drawBackButton();
}

void ViewMusicPlayer::setValuesFalse() {
    playPauseButtonSelected = false;
    nextButtonSelected = false;
    viewBackSelected = false;
    viewSettingsSelected = false;
}
