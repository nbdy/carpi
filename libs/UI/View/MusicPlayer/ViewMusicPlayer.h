//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWMUSICPLAYER_H
#define CARPI_VIEWMUSICPLAYER_H

#include <string>
#include "../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewMusicPlayer : public ViewWithBackAndSettings {
protected:
    MusicLibrary *library;

    bool playPauseButtonSelected = false;
    bool nextButtonSelected = false;

    std::string playPauseButtonText = ">";

    SongInformation currentSong = {"", "", ""};

public:
    ViewMusicPlayer();
    void show(Manager* mgr) override;
    void drawBaseUI();
    void setValuesFalse() override;
};


#endif //CARPI_VIEWMUSICPLAYER_H
