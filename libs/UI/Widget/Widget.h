//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_WIDGET_H
#define CARPI_WIDGET_H

#include "../../Manager/Manager.h"

class Widget {
protected:
    int sizeX{};
    int sizeY{};
    int posX{};
    int posY{};

    // todo make color customizable
public:
    Widget();
    virtual void show(Manager* mgr);
    void _baseUI() const;
};

class MusicPlayerWidget : public Widget {
public:
    MusicPlayerWidget(){
        sizeX = 300;
        sizeY = 200;
        posX = 8;
        posY = 300;
    }

    void show(Manager* mgr) override {
        _baseUI(); // todo small player interface
    }
};


#endif //CARPI_WIDGET_H
