//
// Created by nbdy on 11.06.20.
//

#include "Key.h"

#define RAYGUI_STATIC
#include "../../../raygui/raygui.h"

bool Key::draw(float x, float y) {
    return GuiButton((Rectangle){y, x, sizeX, sizeY}, key.c_str());
}

bool Key::isPressed(const std::string &data) {
    return isPressed(data, value);
}

Key::Key() = default;