//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWMAP_H
#define CARPI_VIEWMAP_H


#include "../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewMap : public ViewWithBackAndSettings {
private:
    int zoomLevel = 16;
    std::string tileName;
    std::pair<int, int> size = {560, 560}; // todo get target resolution from config
    Position *tmpPosition = nullptr;
    bool lockedToTmpPosition = false;
    Texture2D tmpTex;
    Texture2D cpIndicator;
    std::pair<int, int> offset = {8, 8};

public:
    ViewMap();
    ~ViewMap();
    void drawCurrentPositionIndicator(double rotation);
    void drawMap(Manager* mgr);
    void incrementZoomLevel();// only exists to prevent going too deep
    void decrementZoomLevel();// should not be able to zoom below 0; but hey.. users
    void handleTouchStuff(Manager *mgr);
    void drawOutline();
    void drawControlButtons(Manager *mgr);
    void drawMapInformation();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWMAP_H
