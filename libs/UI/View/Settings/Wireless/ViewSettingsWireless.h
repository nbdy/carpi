//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSWIRELESS_H
#define CARPI_VIEWSETTINGSWIRELESS_H


#include "../../WithBack/ViewWithBack.h"

class ViewSettingsWireless : public ViewWithBack {
private:
    bool viewBluetoothSettingsSelected = false;
    bool viewWifiSettingsSelected = false;
    bool viewHackRFSettingsSelected = false;

public:
    ViewSettingsWireless();
    void show(Manager* mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};

#endif //CARPI_VIEWSETTINGSWIRELESS_H
