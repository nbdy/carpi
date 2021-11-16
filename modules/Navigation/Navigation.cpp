//
// Created by nbdy on 10.10.21.
//

#include "Navigation.h"

Navigation::Navigation(): IModule(ModuleInformation {"Navigation"}), map(SCREEN_WIDTH - MODULE_SCROLLER_WIDTH, SCREEN_HEIGHT) {
  // mapnik::load_map(map, )
}

void Navigation::draw(uint32_t i_uWidth, uint32_t i_uHeight) {

}

F_CREATE(Navigation)
