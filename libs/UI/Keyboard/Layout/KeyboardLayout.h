//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_KEYBOARDLAYOUT_H
#define CARPI_KEYBOARDLAYOUT_H

#include <vector>
#include <string>
#include "../Row/KeyboardRow.h"

class KeyboardLayout {
private:
    std::vector<KeyboardRow*> rows;

public:
    KeyboardLayout();
    std::string draw();
    std::string draw(std::string base);
};


#endif //CARPI_KEYBOARDLAYOUT_H
