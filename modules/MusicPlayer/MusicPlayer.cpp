//
// Created by nbdy on 17.11.21.
//

#include "MusicPlayer.h"

#include "raygui.h"

#define BUTTON(mx, my, w, h, s) GuiButton(Rectangle {static_cast<float>(mx), static_cast<float>(my), w, h}, s)

MusicPlayer::MusicPlayer(): IModule(ModuleInformation{"MusicPlayer"}) {}

MusicPlayer::MusicPlayer(std::vector<std::string> i_vLibraryPaths): IModule(ModuleInformation{"MusicPlayer"}) {}

void MusicPlayer::draw(float i_fX, float i_fY) {
  drawUiButtons(i_fX, i_fY);
}

void MusicPlayer::drawUiButtons(float i_fX, float i_fY) {
  if(BUTTON(i_fX, i_fY, 100, 50, "Library")) {
    DLOG("Library button clicked");
  } else if(BUTTON(i_fX + 100, i_fY, 100, 50, "Playlist")) {
    DLOG("Playlist button clicked");
  } else if(BUTTON(i_fX + 200, i_fY, 200, 50, "Current Song")) {
    DLOG("Current song button clicked");
  } else if(BUTTON(i_fX + 400, i_fY, 100, 50, "Albums")) {
    DLOG("Albums button clicked");
  } else if(BUTTON(i_fX + 500, i_fY, 100, 50, "Settings")) {
    DLOG("Settings button clicked");
  }
}

F_CREATE(MusicPlayer)
