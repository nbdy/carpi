//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSAUDIORADIO_H
#define CARPI_VIEWSETTINGSAUDIORADIO_H


#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsAudioRadio : public ViewWithBack {
private:
    float frequencySliderValue = 0;
public:
    ViewSettingsAudioRadio();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
    float getFrequencySliderValue();
};


#endif //CARPI_VIEWSETTINGSAUDIORADIO_H
