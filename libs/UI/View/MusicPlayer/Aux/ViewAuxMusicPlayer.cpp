//
// Created by insane on 14.06.20.
//

#include "ViewAuxMusicPlayer.h"

ViewAuxMusicPlayer::ViewAuxMusicPlayer() {
    library = new MusicLibrary();
    player = new MusicPlayer(library); // todo actually take the argument from the config file
    setName("audio aux");
    setParent("audio");
    playerThread = player->getThread();
}

void ViewAuxMusicPlayer::show(Manager *mgr) {
    drawBaseUI();
    player->setDontRepeat(GuiCheckBox(Rectangle{8, 420, 42, 42}, "dont repeat", player->getDontRepeat()));
    if(playPauseButtonSelected) player->playPause();
    if(nextButtonSelected) player->next();
    if(player->getIsPaused() || !player->getIsPlaying()) playPauseButtonText = ">";
    else playPauseButtonText = "| |";
    currentSong = player->getCurrentSong();
    GuiLabel((Rectangle){8, 8, 35, 128}, currentSong.artist.c_str());
    GuiLabel((Rectangle){8, 48, 35, 128}, currentSong.album.c_str());
    GuiLabel((Rectangle){8, 88, 35, 128}, currentSong.title.c_str());
    off_t cp = player->getPosition();
    double cv = player->getVolume();
    double np = GuiSlider((Rectangle){64, 180, 420, 42}, "pos", TextFormat("%2.2f", player->getPosition()), 0, player->getLength(), false);
    double nv = GuiSliderBar((Rectangle){64, 240, 420, 42}, "vol", TextFormat("%2.2f", (float) player->getVolume()), 0, 10, false);
    if(cp != np) player->setPosition((off_t) np);
    if(cv != nv) player->setVolume(nv);
}

ViewAuxMusicPlayer::~ViewAuxMusicPlayer() {
    playerThread.join();
}
