//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_SIDEBAR_H
#define CARPI_SIDEBAR_H


#include "../../Manager/Manager.h"

class Sidebar { // todo fix affecting elements under sidebar
private:
    float basePositionX = 758;
    int posX = 758;
    int posY = 84;
    int sizeX = 820;
    int sizeY = 364;
    int sizePuller = 42;
    float lockPositionX1 = 420;
    float lockPositionX2 = 642;

    Manager *mgr;

public:
    ~Sidebar()= default;

    explicit Sidebar(Manager *mgr);
    void show();
};


#endif //CARPI_SIDEBAR_H
