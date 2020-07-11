//
// Created by nbdy on 11.06.20.
//

#include "KeyboardLayout.h"


KeyboardLayout::KeyboardLayout() {
    rows = {new KeyboardRow0(), new KeyboardRow1(), new KeyboardRow2(), new KeyboardRow3(), new KeyboardRow4()};
}

std::string KeyboardLayout::draw(std::string base) {
    int indexFromEnd = 0; // todo index from bottom
    float x = 420;
    float y = 8;
    for(KeyboardRow* kbr : rows){
        x -= (kbr->getAverageSizeY() + 4);
        std::string v = kbr->draw(x, y);
        if(KeyBackspace::isPressed(v)) base = base.substr(0, base.size() - 1); // todo fix with indexFromEnd
        else if(v == "{{{shift}}}") continue; // todo next char uppercase
        else if(KeyLeft::isPressed(v)) {if((indexFromEnd + 1) < base.size()) indexFromEnd += 1;}
        else if(KeyRight::isPressed(v)) {if((indexFromEnd - 1) > 0) indexFromEnd -= 1;}
        else base += v;
    }
    return base;
}

std::string KeyboardLayout::draw() {
    return draw("");
}
