//
// Created by insane on 08.02.19.
//

#ifndef CARPI_WIFISCANNER_H
#define CARPI_WIFISCANNER_H

#include <unistd.h>
#include <tins/tins.h>
#include "../Runnable/Runnable.h"
#include "../Network/Network.h"
#include "../Device/Device.h"


class WifiPacket : public Packet {
public:
    explicit WifiPacket(Tins::Packet &pkt);
};

class WifiPackets {
private:
    std::vector<WifiPacket*> packets;

public:
    std::vector<WifiPacket*> getPackets();
    std::vector<WifiPacket*> getByAddress(const std::string& address);
    std::vector<WifiPacket*> getByDevice(Device& device);
    std::vector<WifiPacket*> getByAddress(const std::string& address, bool bySender);  // else by receiver
    std::vector<WifiPacket*> getByDevice(Device& device, bool bySender);

    void addPacket(WifiPacket* packet);
};

class ScanResult {
private:
    clock_t startTime;
    clock_t endTime;
    WifiPackets* packets;

public:
    ScanResult();

    WifiPackets* getPackets();
    WifiPackets* getPackets(const std::string& address);
    WifiPackets* getPackets(Device& device);

    void add(Tins::Packet& pkt);
    void setStartTime(clock_t t);
    void setEndTime(clock_t t);
    clock_t getStartTime();
    clock_t getEndTime();
};

class WifiScanner : public Runnable{
private:
    Network *network;

    bool promiscuous = true;
    std::string interface;

    void enableMonitorMode(const std::string& interface);
    void disableMonitorMode(const std::string& interface);

public:
    explicit WifiScanner(Network *network);
    ~WifiScanner();

    ScanResult* scanFor(int seconds);

    void run() override;
    void stop() override;
};


#endif //CARPI_WIFISCANNER_H
