//
// Created by nbdy on 11.10.21.
//

#ifndef CARPI_MODULES_WIFI_WIFI_H_
#define CARPI_MODULES_WIFI_WIFI_H_

#define USE_OHLOG
#define ENABLE_DRAW_FUNCTION
#include "modulepp.h"
#include <tins/dot11.h>

struct WiFiDevice {

};

class WiFi : public IModule {
public:
  WiFi();

#ifdef ENABLE_DRAW_FUNCTION
  void draw(float i_fX, float i_fY) override;
#endif

  void processDot11Frame(const Tins::Dot11 &dot11);
  void sniff();
};

#endif // CARPI_MODULES_WIFI_WIFI_H_
