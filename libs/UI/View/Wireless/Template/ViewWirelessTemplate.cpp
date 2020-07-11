//
// Created by insane on 14.06.20.
//

#include "ViewWirelessTemplate.h"

ViewWirelessTemplate::ViewWirelessTemplate() {
    _overrideCatchAll();
}

void ViewWirelessTemplate::show(Manager *mgr) {
    _overrideCatchAll();
}

void ViewWirelessTemplate::setValuesFalse() {
    _overrideCatchAll();
}

void ViewWirelessTemplate::drawInterfaceList(Manager *mgr) {
    if(GuiDropdownBox((Rectangle){8, 8, 224, 42}, joinedInterfaceList.c_str(), &interfaceDropdownSelectedItem, interfaceDropdownEditMode))
        interfaceDropdownEditMode = !interfaceDropdownEditMode;
}

std::string ViewWirelessTemplate::getSelectedInterfaceName() {
    if(interfaceList.empty()) return "";
    return interfaceList[interfaceDropdownSelectedItem];
}

void ViewWirelessTemplate::drawScanButton() {
    if(GuiButton((Rectangle) {242, 8, 84, 42}, "scan")) scanButtonSelected = !scanButtonSelected;
}

void ViewWirelessTemplate::scan(Manager *mgr) {

}

void ViewWirelessTemplate::drawScanningInformation() {
    std::string tmp = "scanning (" + getSelectedInterfaceName() + ")";
    if(scanButtonSelected && !isDoneScanning) GuiLabel((Rectangle) {8, 50, 142, 42}, tmp.c_str());
    else if(scanButtonSelected && isDoneScanning) GuiLabel(Rectangle{8, 50, 142, 42}, "done scanning");
}

void ViewWirelessTemplate::drawFoundDevices() {
    if(isDoneScanning){
        if(!foundDevices->isEmpty()) {
            if(GuiListView((Rectangle) {8, 64, 256, 420},
                           Utils::joinList(foundDevices->getAddresses(), ";").c_str(), &selectedDeviceIndex,
                           selectedDevicesActive)) selectedDevicesEditMode = !selectedDevicesEditMode;
        } else {
            GuiLabel((Rectangle){8, 100, 142, 42}, "couldn't find any devices");
            // todo draw reset button
        }
    }
}

void ViewWirelessTemplate::setFoundDevices(Devices *devices) {
    setIsDoneScanning(true);
    foundDevices = devices;
    std::cout << Utils::joinList(foundDevices->getAddresses(), ";") << std::endl;
}

void ViewWirelessTemplate::setIsDoneScanning(bool value) {
    isDoneScanning = value;
}
