//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWIRELESSTEMPLATE_H
#define CARPI_VIEWWIRELESSTEMPLATE_H

#include <string>
#include <vector>
#include "../../WithBackAndSettings/ViewWithBackAndSettings.h"
#include "../../../../Device/Device.h"

class ViewWirelessTemplate : public ViewWithBackAndSettings {
protected:
    bool interfaceDropdownEditMode = false;
    bool interfaceDropdownSelected = false;
    int interfaceDropdownSelectedItem = 0;
    std::vector<std::string> interfaceList;
    std::string joinedInterfaceList;
    bool isDoneScanning = false;
    Devices* foundDevices;
    bool selectedDevicesEditMode = false;
    int selectedDeviceIndex = 0;
    int selectedDevicesActive = -1;

    bool scanButtonSelected = false;

public:
    ViewWirelessTemplate();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
    void drawInterfaceList(Manager* mgr);
    std::string getSelectedInterfaceName();
    void drawScanButton();
    virtual void scan(Manager* mgr);
    void drawScanningInformation();
    void drawFoundDevices();
    void setFoundDevices(Devices *devices);
    void setIsDoneScanning(bool value);
};


#endif //CARPI_VIEWWIRELESSTEMPLATE_H
