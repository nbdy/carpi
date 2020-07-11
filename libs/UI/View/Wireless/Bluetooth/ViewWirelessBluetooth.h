//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWWIRELESSBLUETOOTH_H
#define CARPI_VIEWWIRELESSBLUETOOTH_H


#include "../Template/ViewWirelessTemplate.h"
#include "../../../../BluetoothScanner/BluetoothScanner.h"

class ViewWirelessBluetooth : public ViewWirelessTemplate {
private:
    BluetoothScanner* bluetoothScanner = nullptr;

public:
    ViewWirelessBluetooth();
    void show(Manager* mgr) override;
    void scan(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWWIRELESSBLUETOOTH_H
