//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWAUXMUSICPLAYER_H
#define CARPI_VIEWAUXMUSICPLAYER_H

#include <thread>

#include "../ViewMusicPlayer.h"
#include "../../../../MusicPlayer/MusicPlayer.h"

class ViewAuxMusicPlayer : public ViewMusicPlayer {
private:
    MusicPlayer *player;
    std::thread playerThread;

public:
    ViewAuxMusicPlayer();
    void show(Manager* mgr) override;
    ~ViewAuxMusicPlayer();
};


#endif //CARPI_VIEWAUXMUSICPLAYER_H
