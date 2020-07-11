//
// Created by insane on 24.02.19.
//

#include "BluetoothScanner.h"
#include "../Utils/Utils.h"

Devices* BluetoothScanner::scan(int seconds) {
    scanning = true;
    auto devices = new Devices();
    inquiry_info *ii = nullptr;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };
    dev_id = hci_get_route(nullptr);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) return devices;
    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    num_rsp = hci_inquiry(dev_id, len, max_rsp, nullptr, &ii, flags);
    if( num_rsp < 0 ) return devices;
    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0) strcpy(name, "");
        devices->addDevice(new BluetoothDevice(addr, name));
    }
    free(ii);
    close(sock);
    scanning = false;
    return devices;
}

std::vector<BluetoothDevice*> BluetoothScanner::getByName(const std::vector<BluetoothDevice*>& devices, const std::string& name, bool contains) {
    std::vector<BluetoothDevice*> r;
    for(BluetoothDevice* device : devices) {
        if(contains){
            if(Utils::contains(device->getName(), name)) r.emplace_back(device);
        } else {
            if(device->getName() == name) r.emplace_back(device);
        }
    }
    return r;
}

bool BluetoothScanner::isScanning() {return scanning;}

BluetoothDevice::BluetoothDevice() {}

BluetoothDevice::BluetoothDevice(const std::string& address, const std::string& name) {
    setAddress(address);
    setName(name);
}

void BluetoothDevice::setName(const std::string &name) {
    this->name = name;
}

std::string BluetoothDevice::getName() {return name;}