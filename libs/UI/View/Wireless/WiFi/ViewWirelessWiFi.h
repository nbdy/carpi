//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWIRELESSWIFI_H
#define CARPI_VIEWWIRELESSWIFI_H


#include "../Template/ViewWirelessTemplate.h"

class ViewWirelessWiFi : public ViewWirelessTemplate {
private:
    bool promiscuousCheckboxChecked = false;

public:
    explicit ViewWirelessWiFi();
    void drawPromiscuousCheckbox();
    void scan(Manager* mgr) override;
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWWIRELESSWIFI_H
