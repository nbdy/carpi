//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWRADIOMUSICPLAYER_H
#define CARPI_VIEWRADIOMUSICPLAYER_H

#include "../ViewMusicPlayer.h"

class ViewRadioMusicPlayer : public ViewMusicPlayer {
public:
    ViewRadioMusicPlayer();
    void show(Manager* mgr) override;
};


#endif //CARPI_VIEWRADIOMUSICPLAYER_H
