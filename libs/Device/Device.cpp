//
// Created by insane on 08.02.19.
//

#include "Device.h"
#include "../Utils/Utils.h"

Devices::Devices() {
    devices = {};
}

Devices::Devices(const std::vector<Device*>& devices) {
    this->devices = devices;
}

std::vector<std::string> Devices::getAddresses(std::vector<Device*> devices) {
    std::vector<std::string> r;
    for(Device *d : devices) r.emplace_back(d->getAddress());
    return r;
}

std::vector<Device*> Devices::getByAddress(const Devices &devices, const std::string &address) {
    std::vector<Device*> r;
    for(Device *d : devices.devices){ if(d->getAddress() == address) r.emplace_back(d); }
    return r;
}

std::vector<Device*> Devices::getByAddress(const std::string &address, bool startsWith) {
    std::vector<Device*> r;
    for(Device *device : devices){
        if(startsWith){
            if(Utils::startsWith(device->getAddress(), address)) r.emplace_back(device);
        } else {
            if(Utils::endsWith(device->getAddress(), address)) r.emplace_back(device);
        }
    }
    return r;
}

Device* Devices::getByAddress(const std::string &address) {
    for(Device *device : devices){
        if(device->getAddress() == address) return device;
    }
    return nullptr;
}

std::vector<std::string> Devices::getAddresses() {
    return getAddresses(devices);
}

std::vector<Device*> Devices::getDevices() {return devices;}

bool Devices::isEmpty() {return devices.empty();}

std::string Device::getAddress() {
    return address;
}

void Device::setAddress(std::string address) {
    this->address = std::move(address);
}

void Devices::addDevice(Device *device) {devices.emplace_back(device);}

void Device::setPosition(std::string position) {}


void Packet::setSender(const std::string &value) {sender = value;}

std::string Packet::getSender() {return sender;}

void Packet::setReceiver(const std::string &value) {receiver = value;}

std::string Packet::getReceiver() {return receiver;}

std::string Packet::getTimestamp() { return timestamp;}

std::string Packet::getData() {return data;}

void Packet::setData(const std::string &value) {data = value;}

Device::Device() {

}