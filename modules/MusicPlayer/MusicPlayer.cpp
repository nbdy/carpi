//
// Created by nbdy on 17.11.21.
//

#include "MusicPlayer.h"

#define BUTTON(mx, my, w, h, s) GuiButton(Rectangle {static_cast<float>(mx), static_cast<float>(my), w, h}, s)

MusicPlayer::MusicPlayer(): IModule(ModuleInformation{"MusicPlayer"}) {}

MusicPlayer::MusicPlayer(std::vector<std::string> i_vLibraryPaths): IModule(ModuleInformation{"MusicPlayer"}) {}

void MusicPlayer::draw(float i_fX, float i_fY) {
  drawUiButtons(i_fX, i_fY);
}

void MusicPlayer::drawLibraryUi() {}

void MusicPlayer::drawPlaylistUi() {}

void MusicPlayer::drawCurrentSongUi() {}

void MusicPlayer::drawAlbumsUi() {}

void MusicPlayer::drawSettingsUi() {}

void MusicPlayer::drawUiButtons(float i_fX, float i_fY) {
  if(BUTTON(i_fX, i_fY, 100, 50, "Library")) {
    DLOG("Library button clicked");
    m_SelectedUi = LIBRARY;
  } else if(BUTTON(i_fX + 100, i_fY, 100, 50, "Playlist")) {
    DLOG("Playlist button clicked");
    m_SelectedUi = PLAYLIST;
  } else if(BUTTON(i_fX + 200, i_fY, 250, 50, "Current Song")) {
    DLOG("Current song button clicked");
    m_SelectedUi = CURRENT_SONG;
  } else if(BUTTON(i_fX + 450, i_fY, 100, 50, "Albums")) {
    DLOG("Albums button clicked");
    m_SelectedUi = ALBUMS;
  } else if(BUTTON(i_fX + 550, i_fY, 100, 50, "Settings")) {
    DLOG("Settings button clicked");
    m_SelectedUi = SETTINGS;
  }
}

F_CREATE(MusicPlayer)
