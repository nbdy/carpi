//
// Created by nbdy on 11.06.20.
//

#include "KeyboardRow.h"

KeyboardRow::KeyboardRow() = default;

float KeyboardRow::getAverageSizeX() {
    float x = 0;
    float c = 0;
    for(Key* k : row){
        x += k->sizeX;
        c += 1;
    }
    return x / c;
}

float KeyboardRow::getAverageSizeY() {
    float y = 0;
    float c = 0;
    for(Key* k : row){
        y += k->sizeX;
        c += 1;
    }
    return y / c;
}

std::string KeyboardRow::_draw(float x, float y) {
    std::string r;
    for(Key* k : row){
        if(k->draw(x, y)) r += k->value;
        y += (k->sizeX + 4);
    }
    return r;
}

std::tuple<float, float> KeyboardRow::getAverageSize() {
    return std::tuple<float, float>{getAverageSizeX(), getAverageSizeY()};
}

std::string KeyboardRow::draw(float x, float y) {
    return _draw(x, y);
}
