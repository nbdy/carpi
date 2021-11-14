//
// Created by nbdy on 11.10.21.
//

#ifndef CARPI_MODULES_WIFI_WIFI_H_
#define CARPI_MODULES_WIFI_WIFI_H_

#include <tins/dot11.h>

#include "Module/Module.h"

struct WiFiDevice {

};

class WiFi : public Module {
public:
  WiFi();

  void processDot11Frame(const Tins::Dot11 &dot11) {
    if(dot11.find_pdu<Tins::Dot11Beacon>()){
      const auto& beacon = dot11.rfind_pdu<Tins::Dot11Beacon>();
      std::cout << "beacon:" << std::endl;
      std::cout << "\taddr1: " << beacon.addr1().to_string() << std::endl;
      std::cout << "\taddr2: " << beacon.addr2().to_string() << std::endl;
      std::cout << "\taddr3: " << beacon.addr3().to_string() << std::endl;
      std::cout << "\taddr4: " << beacon.addr4().to_string() << std::endl;
    }
    if(dot11.find_pdu<Tins::Dot11ProbeRequest>()){
      const auto& probeReq = dot11.rfind_pdu<Tins::Dot11ProbeRequest>();
      std::cout << "probeRequest:" << std::endl;
      std::cout << "\taddr1: " + probeReq.addr1().to_string() << std::endl;
      std::cout << "\taddr2: " + probeReq.addr2().to_string() << std::endl;
      std::cout << "\taddr3: " + probeReq.addr3().to_string() << std::endl;
      std::cout << "\taddr4: " + probeReq.addr4().to_string() << std::endl;
    }
  }

  void sniff() {

  }

};

#endif // CARPI_MODULES_WIFI_WIFI_H_
