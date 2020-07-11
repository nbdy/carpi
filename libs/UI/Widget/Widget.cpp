//
// Created by nbdy on 11.06.20.
//

#include <raylib.h>
#include "Widget.h"

void Widget::_baseUI() const {
    // todo get mousepointer and set position
    DrawRectangle(posX, posY, sizeX, sizeY, RAYWHITE);
    DrawRectangle(posX + 2, posY + 2, sizeX - 4, 20 - 4, BLACK);
    DrawRectangle(posX + 22, posY + 2, sizeX - 4, sizeY - 20, BLACK);
}

void Widget::show(Manager *mgr) {

}

Widget::Widget() = default;
