//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSAUDIO_H
#define CARPI_VIEWSETTINGSAUDIO_H


#include "../../WithBack/ViewWithBack.h"

class ViewSettingsAudio : public ViewWithBack {
    bool viewAudioAuxSettings = false;
    bool viewAudioRadioSettings = false;

public:
    ViewSettingsAudio();
    void show(Manager* mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSAUDIO_H
