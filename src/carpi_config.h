//
// Created by nbdy on 10.10.21.
//

#ifndef CARPI__CONFIG_H_
#define CARPI__CONFIG_H_

#define USE_OHLOG
#define ENABLE_DRAW_FUNCTION

#include "ext/ohlog.h"
#include "ext/modulepp.h"

constexpr char APPLICATION_NAME[] = "carpi";
constexpr char MODULE_DIRECTORY[] = "modules/";

constexpr uint32_t SCREEN_WIDTH = 800;
constexpr uint32_t SCREEN_HEIGHT = 600;
constexpr uint32_t MODULE_SCROLLER_WIDTH = SCREEN_WIDTH / 5;
constexpr uint32_t MODULE_CONTENT_OFFSET = MODULE_SCROLLER_WIDTH + 8;

constexpr uint32_t ERROR_NONE = 0;
constexpr uint32_t ERROR_WINDOW_CREATION = 1;
constexpr uint32_t ERROR_CONFIGURATION = 2;

#endif // CARPI__CONFIG_H_
