//
// Created by insane on 08.02.19.
//

#include "WifiScanner.h"


WifiScanner::WifiScanner(Network *nicManager) {
    setName("wifi scanner");
    setDoRun(true);

    this->network = nicManager;
    interface = nicManager->getWifiInterface();
    if(interface.empty()) setDoRun(false);
    else {
        if(promiscuous && !Utils::endsWith(interface, "mon")) enableMonitorMode(interface);
        else if(!promiscuous && Utils::endsWith(interface, "mon")) disableMonitorMode(interface);
    }
}

void WifiScanner::run() {
    if(!getDoRun()) return;
    Tins::SnifferConfiguration scfg;
    scfg.set_promisc_mode(promiscuous);
}

void WifiScanner::stop() {
    setDoRun(false);
    if(Utils::endsWith(interface, "mon")) disableMonitorMode(interface);
}

WifiScanner::~WifiScanner() {

}

void WifiScanner::enableMonitorMode(const std::string &interface) {
    if (network->checkInterfaceUsed(interface)) return;
    std::string t = "airmon-ng start " + interface;
    system(t.c_str());
}

void WifiScanner::disableMonitorMode(const std::string &interface) {
    std::string t = "airmon-ng stop " + interface;
    system(t.c_str());
}

WifiPacket::WifiPacket(Tins::Packet& pkt) {
    const Tins::Dot11& dot11 = pkt.pdu()->rfind_pdu<Tins::Dot11>();

}

std::vector<WifiPacket*> WifiPackets::getByAddress(const std::string &address) {
    std::vector<WifiPacket*> r;
    for(WifiPacket *p : packets) {
        if(p->getSender() == address) r.emplace_back(p);
        if(p->getReceiver() == address) r.emplace_back(p);
    }
    return r;
}

std::vector<WifiPacket*> WifiPackets::getByDevice(Device &device) {
    std::vector<WifiPacket*> r;
    for(WifiPacket *p : packets) {
        if(p->getSender() == device.getAddress()) r.emplace_back(p);
        if(p->getReceiver() == device.getAddress()) r.emplace_back(p);
    }
    return r;
}

std::vector<WifiPacket*> WifiPackets::getByAddress(const std::string &address, bool bySender) {
    std::vector<WifiPacket*> r;
    for(WifiPacket *p : packets){
        if(bySender) {
            if(p->getSender() == address) r.emplace_back(p);
        } else {
            if(p->getReceiver() == address) r.emplace_back(p);
        }
    }
    return r;
}

std::vector<WifiPacket*> WifiPackets::getByDevice(Device &device, bool bySender) {
    std::vector<WifiPacket*> r;
    for(WifiPacket *p : packets){
        if(bySender) {
            if(p->getSender() == device.getAddress()) r.emplace_back(p);
        } else {
            if(p->getReceiver() == device.getAddress()) r.emplace_back(p);
        }
    }
    return r;
}

std::vector<WifiPacket*> WifiPackets::getPackets() {
    return packets;
}

void ScanResult::add(Tins::Packet& pkt) {
    packets->addPacket(new WifiPacket(pkt));
}

ScanResult* WifiScanner::scanFor(int seconds) {
    auto *r = new ScanResult();
    r->setStartTime(std::clock());
    bool doScan = true;
    Tins::SnifferConfiguration sc;
    sc.set_promisc_mode(promiscuous);
    Tins::Sniffer s(interface, sc);
    while(doScan){
        if((float(clock () - r->getStartTime()) /  CLOCKS_PER_SEC) == seconds) doScan = false;
        for(auto& pkt : s) r->add(pkt);
    }
    r->setEndTime(clock());
    return r;
}

void ScanResult::setStartTime(clock_t t) {startTime = t;}

void ScanResult::setEndTime(clock_t t) {endTime = t;}

clock_t ScanResult::getStartTime() {return startTime;}

clock_t ScanResult::getEndTime() {return endTime;}

WifiPackets* ScanResult::getPackets() {return packets;}

WifiPackets* ScanResult::getPackets(Device &device) {
    auto *r = new WifiPackets();
    for(WifiPacket *p : packets->getPackets()){if(p->getReceiver() == device.getAddress() || p->getSender() == device.getAddress()) r->addPacket(p);}
    return r;
}

WifiPackets* ScanResult::getPackets(const std::string &address) {
    auto *r = new WifiPackets();
    for(WifiPacket *p : packets->getPackets()) {if(p->getReceiver() == address || p->getSender() == address) r->addPacket(p);}
    return r;
}

void WifiPackets::addPacket(WifiPacket *packet) {
    packets.emplace_back(packet);
}

ScanResult::ScanResult() {

}