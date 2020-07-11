//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWAUDIO_H
#define CARPI_VIEWAUDIO_H


#include "../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewAudio : public ViewWithBackAndSettings {
private:
    bool viewAudioAuxSelected = false;
    bool viewAudioRadioSelected = false;

public:
    ViewAudio();
    void show(Manager* mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWAUDIO_H
