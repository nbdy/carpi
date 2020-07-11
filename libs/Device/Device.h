//
// Created by insane on 08.02.19.
//

#ifndef CARPI_DEVICE_H
#define CARPI_DEVICE_H


#include <string>
#include <vector>
#include "../GPS/GPS.h"

class Device {
private:
    std::string address;
    std::string positionsTable;

public:
    Device();
    explicit Device(const std::string& address);

    std::string getAddress();
    void setAddress(std::string address);

    void setPosition(std::string position);
};

class Packet {
private:
    std::string sender;
    std::string receiver;
    std::string data;
    std::string timestamp;

public:
    std::string getSender();
    void setSender(const std::string& value);

    std::string getReceiver();
    void setReceiver(const std::string& value);

    std::string getData();
    void setData(const std::string& value);

    std::string getTimestamp();
};

class Devices {
private:
    std::vector<Device*> devices;

public:
    Devices();
    explicit Devices(const std::vector<Device*>& devices);

    std::vector<Device*> getDevices();
    std::vector<std::string> getAddresses();
    std::vector<Device*> getByAddress(const std::string& address, bool endsWith);  // else startswith
    Device *getByAddress(const std::string& address); // returns nullptr if not in devices
    bool isEmpty();

    static std::vector<std::string> getAddresses(std::vector<Device*> devices);
    static std::vector<Device*> getByAddress(const Devices& devices, const std::string& address);

    void addDevice(Device* device);
};


#endif //CARPI_DEVICE_H
