//
// Created by nbdy on 17.11.21.
//

#ifndef CARPI_MODULES_MUSICPLAYER_MUSICPLAYER_H_
#define CARPI_MODULES_MUSICPLAYER_MUSICPLAYER_H_

#include <SFML/Audio.hpp>

#define ENABLE_DRAW_FUNCTION

#include "modulepp.h"

class MusicPlayer : public IModule {
  enum SelectedUi {
    LIBRARY = 0, PLAYLIST, CURRENT_SONG, ALBUMS, SETTINGS
  };

  SelectedUi m_SelectedUi = CURRENT_SONG;
  bool m_bPlay = false;

  void drawLibraryUi();
  void drawPlaylistUi();
  void drawCurrentSongUi();
  void drawAlbumsUi();
  void drawSettingsUi();

public:
  MusicPlayer();
  explicit MusicPlayer(std::vector<std::string> i_vLibraryPaths);

  void drawUiButtons(float i_fX, float i_fY);
  void draw(float i_fX, float i_fY) override;

};

#endif // CARPI_MODULES_MUSICPLAYER_MUSICPLAYER_H_
