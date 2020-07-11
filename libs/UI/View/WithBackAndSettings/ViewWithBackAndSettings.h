//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWITHBACKANDSETTINGS_H
#define CARPI_VIEWWITHBACKANDSETTINGS_H

#include <string>
#include "../WithBack/ViewWithBack.h"

class ViewWithBackAndSettings : public ViewWithBack {
protected:
    bool viewSettingsSelected = false;

public:
    ViewWithBackAndSettings();
    void drawSettingsButton();
    std::string getNextView() override;
    bool getViewSettingsSelected();
};


#endif //CARPI_VIEWWITHBACKANDSETTINGS_H
