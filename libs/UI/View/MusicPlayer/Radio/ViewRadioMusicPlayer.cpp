//
// Created by insane on 14.06.20.
//

#include "ViewRadioMusicPlayer.h"

ViewRadioMusicPlayer::ViewRadioMusicPlayer() {
    setName("audio radio");
    setParent("audio");
}

void ViewRadioMusicPlayer::show(Manager *mgr) {
    drawBaseUI();
}
