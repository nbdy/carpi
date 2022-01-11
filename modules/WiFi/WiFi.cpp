//
// Created by nbdy on 11.10.21.
//

#include "WiFi.h"

WiFi::WiFi(): IModule(ModuleInformation {"WiFi"}) {}

void WiFi::processDot11Frame(const Tins::Dot11 &dot11) {
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

void WiFi::sniff() {

}

#ifdef ENABLE_DRAW_FUNCTION
void WiFi::draw(float i_fX, float i_fY) {
  static float xOffset = i_fX + 8;
  GuiLabel(Rectangle{xOffset, i_fY, 64, 16}, "WiFi");
}
#endif

F_CREATE(WiFi)