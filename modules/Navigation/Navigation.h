//
// Created by nbdy on 10.10.21.
//

#ifndef CARPI_MODULES_NAVIGATION_NAVIGATION_H_
#define CARPI_MODULES_NAVIGATION_NAVIGATION_H_

#include <mapnik/map.hpp>
#include <mapnik/load_map.hpp>

#include "config.h"
#include "Module/Module.h"

class Navigation : public Module {
private:
  mapnik::Map map;

public:
  Navigation();

  void draw(uint32_t i_uWidth, uint32_t i_uHeight);
};

#endif // CARPI_MODULES_NAVIGATION_NAVIGATION_H_
