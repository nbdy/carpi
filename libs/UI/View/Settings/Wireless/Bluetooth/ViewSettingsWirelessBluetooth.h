//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSWIRELESSBLUETOOTH_H
#define CARPI_VIEWSETTINGSWIRELESSBLUETOOTH_H

#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsWirelessBluetooth : public ViewWithBack {
public:
    ViewSettingsWirelessBluetooth();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSWIRELESSBLUETOOTH_H
