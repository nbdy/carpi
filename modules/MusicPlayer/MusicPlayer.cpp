//
// Created by nbdy on 17.11.21.
//

#include "MusicPlayer.h"

#define BUTTON(mx, my, w, h, s)                                                \
  GuiButton(Rectangle{static_cast<float>(mx), static_cast<float>(my), w, h}, s)

MusicPlayer::MusicPlayer() : IModule(ModuleInformation{"MusicPlayer"}) {
  setCycleTime(500);
}

MusicPlayer::MusicPlayer(std::vector<std::string> i_vLibraryPaths)
    : IModule(ModuleInformation{"MusicPlayer"}) {}

void MusicPlayer::draw(float i_fX, float i_fY) {
  drawUiButtons(i_fX, i_fY);

  switch (m_SelectedUi) {
  case LIBRARY:
    drawLibraryUi();
    break;
  case PLAYLIST:
    drawPlaylistUi();
    break;
  case CURRENT_SONG:
    drawCurrentSongUi();
    break;
  case ALBUMS:
    drawAlbumsUi();
    break;
  case SETTINGS:
    drawSettingsUi();
    break;
  }
}

void MusicPlayer::drawLibraryUi() {
  // TODO(nbdy): Library class
  //             - a map of AliasName : DirectoryPath
  // TODO(nbdy): Top left: EditText, Top right: "+" button if edit text was
  // selected, "-" button if ListView selection != -1
  // TODO(nbdy): Below left to right to bottom: ListView
  // TODO(nbdy): set CurrentSongUi active when Song or Album is tapped a second
  // time and play first / selected song
}

void MusicPlayer::drawPlaylistUi() {
  // TODO(nbdy): Song class
  //             - string Name, Album, Artist, Path, CoverImagePath
  //             - uint64 Timestamp, LastPlayed, PlayCount, LastIndex
  // TODO(nbdy): Playlist class
  //             - string Name
  //             - vector of Song
  // TODO(nbdy): Playlists class
  //             - a map of AliasName : Playlist
  // TODO(nbdy): Bottom Left: Label (playlist count), Label (song count) if
  // playlist selected
  // TODO(nbdy): Top left to middle to top of Bottom row: ListView (playlists)
  // TODO(nbdy): Top right to middle to top of bottom row: ListView (songs) if
  // playlist selected and has songs
  // TODO(nbdy): Bottom Right: Button (remove song / remove playlist depending
  // on if song is selected)
  // TODO(nbdy): set CurrentSongUi active when Song or Playlist is tapped a
  // second time and play first / selected song
}

void MusicPlayer::drawCurrentSongUi() {
  // TODO(nbdy): Button PreviousSongButton, Start-/StopSongButton,
  // NextSongButton
  // TODO(nbdy): Top center: CoverImage
  // TODO(nbdy): Below CoverImage centered: SongInformation (Name, Album,
  // Artist)
  // TODO(nbdy): Below SongInformation from left to right: HorizontalSlider to
  // seek
  // TODO(nbdy): Left of CoverImage: VerticalSlider to set volume
  // TODO(nbdy): Left of VolumeSlider: ListView to select Equalizer
  // TODO(nbdy): Right of CoverImage: Checkbox to enable shuffling
  // TODO(nbdy): Right of CoverImage below ShuffleCheckbox: Checkbox to loop
  // current song
  // TODO(nbdy): Right of CoverImage below LoopCurrentSongCheckbox: Checkbox to
  // loop current album / playlist
}

void MusicPlayer::drawAlbumsUi() {
  // TODO(nbdy): Album class
  //             - string Name, Artist, Path, CoverImagePath
  //             - vector of Song
  // TODO(nbdy): Albums class
  //             - vector of Album
  // TODO(nbdy): Bottom Left: Label (album count), Label (song count) if album
  // selected
  // TODO(nbdy): Top left to middle to top of Bottom row: ListView (albums)
  // TODO(nbdy): Top right to middle to top of bottom row: ListView (songs) if
  // album selected and has songs
  // TODO(nbdy): Bottom Right: Button (remove song / remove album depending on
  // if song is selected)
  // TODO(nbdy): set CurrentSongUi active when Song or Album is tapped a second
  // time and play first / selected song
}

void MusicPlayer::drawSettingsUi() {
  // TODO(nbdy): Settings class
  // TODO(nbdy): Top left to bottom (1 / 5 of screen width) Settings
  // (Equalizers)
  // TODO(nbdy): Equalizer tab: 8 Vertical Sliders for different frequencies
}

void MusicPlayer::drawUiButtons(float i_fX, float i_fY) {
  if (BUTTON(i_fX, i_fY, 100, 50, "Library")) {
    DLOG("Library button clicked");
    m_SelectedUi = LIBRARY;
  } else if (BUTTON(i_fX + 100, i_fY, 100, 50, "Playlist")) {
    DLOG("Playlist button clicked");
    m_SelectedUi = PLAYLIST;
  } else if (BUTTON(i_fX + 200, i_fY, 240, 50, "Current Song")) {
    DLOG("Current song button clicked");
    m_SelectedUi = CURRENT_SONG;
  } else if (BUTTON(i_fX + 440, i_fY, 100, 50, "Albums")) {
    DLOG("Albums button clicked");
    m_SelectedUi = ALBUMS;
  } else if (BUTTON(i_fX + 540, i_fY, 100, 50, "Settings")) {
    DLOG("Settings button clicked");
    m_SelectedUi = SETTINGS;
  }
}

F_CREATE(MusicPlayer)
