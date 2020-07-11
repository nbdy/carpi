//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSWIRELESSWIFI_H
#define CARPI_VIEWSETTINGSWIRELESSWIFI_H


#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsWirelessWiFi : public ViewWithBack {
private:
    std::vector<std::string> interfaces;
    const char* joinedInterfaces;
    int interfacesListViewActive = -1;
    int interfacesListViewIndex = 0;
    bool interfacesListViewEditMode = false;

public:
    ViewSettingsWirelessWiFi();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSWIRELESSWIFI_H
