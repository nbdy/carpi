//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGS_H
#define CARPI_VIEWSETTINGS_H


#include "../WithBack/ViewWithBack.h"

class ViewSettings : public ViewWithBack {
private:
    bool viewGPSSettingsSelected = false;
    bool viewWirelessSettingsSelected = false;
    bool viewAudioSettingsSelected = false;
    bool viewMapSettingsSelected = false;
    bool viewUpdaterSettingsSelected = false;
    bool viewSystemSettingsSelected = false;

public:
    ViewSettings();
    void show(Manager* mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGS_H
