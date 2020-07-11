//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWIRELESS_H
#define CARPI_VIEWWIRELESS_H


#include "../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewWireless : public ViewWithBackAndSettings {
private:
    bool viewBluetoothSelected = false;
    bool viewWiFiSelected = false;
    bool viewHackRFSelected = false;

public:
    ViewWireless();
    void show(Manager *mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWWIRELESS_H
