//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWMAINMENU_H
#define CARPI_VIEWMAINMENU_H

#include <string>
#include "../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewMainMenu : public ViewWithBackAndSettings {
private:
    bool viewAudioSelected = false;
    bool viewWirelessSelected = false;
    bool viewMapSelected = false;
    bool viewFileManagerSelected = false;
    bool viewUpdaterSelected = false;

public:
    ViewMainMenu();
    void show(Manager *mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWMAINMENU_H
