//
// Created by insane on 14.06.20.
//

#include "ViewWirelessBluetooth.h"

ViewWirelessBluetooth::ViewWirelessBluetooth() {
    setName("wireless bluetooth");
    setParent("wireless");
    interfaceList = Network::getBluetoothInterfaces();
    joinedInterfaceList = Utils::joinList(interfaceList, ";");
}

void ViewWirelessBluetooth::show(Manager *mgr) {
    drawBackButton();
    drawSettingsButton();
    drawScanButton();
    drawScanningInformation();
    drawInterfaceList(mgr);
    drawFoundDevices();
    _drawBaseUI();
}

void ViewWirelessBluetooth::scan(Manager *mgr) {
    if(bluetoothScanner == nullptr) bluetoothScanner = mgr->getBluetoothScanner();
    if(scanButtonSelected && !bluetoothScanner->isScanning()) {
        isDoneScanning = false;
        setFoundDevices(bluetoothScanner->scan(3)); // todo non blocking
    }
}

void ViewWirelessBluetooth::setValuesFalse() {
    viewBackSelected = false;
    viewSettingsSelected = false;
}
