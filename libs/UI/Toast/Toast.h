//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_TOAST_H
#define CARPI_TOAST_H

#include <string>

#include <raylib.h>
#include "../../raygui/raygui.h"

class Toast {
protected:
    double ttl = 3;
    double frameCount = 0;
    std::string message;

    float sizeX = 420;
    float sizeY = 42;
    // todo color customization

    float posX = 342;
    float posY = 550;

public:
    ~Toast()= default;

    Toast()= default;

    explicit Toast(double ttl){
        this->ttl = ttl;
    }

    Toast(const std::string& message, double ttl){
        this->ttl = ttl;
        this->message = message;
    }

    bool show(){
        GuiLabel(Rectangle {posX, posY, sizeX, sizeY}, message.c_str());
        frameCount++;
        return frameCount / GetFPS() <= ttl;
    }
};


#endif //CARPI_TOAST_H
