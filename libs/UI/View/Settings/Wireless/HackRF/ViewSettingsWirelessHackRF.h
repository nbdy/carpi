//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSWIRELESSHACKRF_H
#define CARPI_VIEWSETTINGSWIRELESSHACKRF_H


#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsWirelessHackRF : public ViewWithBack {
public:
    ViewSettingsWirelessHackRF();
    void show(Manager* mgr) override;
};


#endif //CARPI_VIEWSETTINGSWIRELESSHACKRF_H
