//
// Created by insane on 24.02.19.
//

#ifndef CARPI_DEVICES_H
#define CARPI_DEVICES_H

#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "../Device/Device.h"

class BluetoothDevice : public Device {
private:
    std::string name;

public:
    BluetoothDevice();
    BluetoothDevice(const std::string& address, const std::string& name);

    std::string getName();
    void setName(const std::string& name);
};

class BluetoothScanner : public Devices {
private:
    bool scanning = false;

public:
    Devices* scan(int seconds);
    static std::vector<BluetoothDevice*> getByName(const std::vector<BluetoothDevice*>& devices, const std::string& name, bool contains);
    bool isScanning();
};


#endif //CARPI_DEVICES_H
