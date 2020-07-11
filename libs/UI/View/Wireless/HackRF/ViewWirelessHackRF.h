//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWIRELESSHACKRF_H
#define CARPI_VIEWWIRELESSHACKRF_H


#include "../../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewWirelessHackRF : public ViewWithBackAndSettings {
public:
    ViewWirelessHackRF();
    void drawSweepUi(); // todo spectrum viewer
    void show(Manager* mgr) override;
    void setValuesFalse() override;
private:
    bool viewSweepUiButtonClicked = false;
};


#endif //CARPI_VIEWWIRELESSHACKRF_H
