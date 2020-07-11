//
// Created by insane on 14.06.20.
//

#include "ViewMap.h"
#include "../../../../raycons/Icons.h"

ViewMap::ViewMap() {
    setName("map"); // todo button to clear cache
    setParent("main menu");
    cpIndicator = LoadTexture("/var/lib/carpi/icons/18dp/baseline_navigation_white_18dp.png");
}

ViewMap::~ViewMap() {
    UnloadTexture(cpIndicator);
}

void ViewMap::drawCurrentPositionIndicator(double rotation) {
    float x = offset.first + size.first / 2;
    float y = offset.second + size.second / 2;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)cpIndicator.width, (float)cpIndicator.height };
    Rectangle destRec = { x, y, (float)cpIndicator.width, (float)cpIndicator.height };
    Icons::navigation(x, y, 16, 16);
    // DrawTexturePro(cpIndicator, sourceRec, destRec, Vector2{0.0f, 0.0f}, rotation, GREEN); // todo calculate orientation and turn im
}

void ViewMap::drawMap(Manager *mgr) {
    std::string nt;
    if(tmpPosition != nullptr && lockedToTmpPosition) nt = mgr->getNavigation()->getImage(tmpPosition, zoomLevel, size.first, size.second);
    else nt = mgr->getNavigation()->getImage(mgr->getPosition(), zoomLevel, size.first, size.second);

    if(tileName != nt) {
        if(!tileName.empty()) UnloadTexture(tmpTex);
        tileName = nt;
        tmpTex = LoadTexture(tileName.c_str());
    }

    DrawTexture(tmpTex, offset.first, offset.second, WHITE);
    drawCurrentPositionIndicator(mgr->getNavigation()->get2DRotation(mgr->getPosition()));
    // todo draw arrow on current position in the direction from last to current position
    // calculate triangle based on moving direction
}

void ViewMap::incrementZoomLevel() {
    if(zoomLevel <= 18) zoomLevel++; // max zoom level seems to be 22
}

void ViewMap::decrementZoomLevel() {
    if(zoomLevel > 0) zoomLevel--;
}

void ViewMap::handleTouchStuff(Manager *mgr) {
    Vector2 tp;
    std::string msg;
    bool isPi = mgr->getIsPi();
    if(isPi) tp = GetTouchPosition(0);
    else tp = GetMousePosition();
    int cg = GetGestureDetected();

    if(cg == GESTURE_NONE) return; // todo wait for a few seconds then zoom map back to current position

    if(CheckCollisionPointRec(tp, Rectangle{8, 8, (float) size.first, (float) size.second})) { // on desktop we currently need to click and scroll right afterwards
        if(cg == GESTURE_DRAG) {
            tmpPosition = Position::calculateDrag(tp.x, tp.y, zoomLevel, mgr->getPosition());
            addToast(new Toast("dragged", 2));
            return;
        }

        if(isPi){
            if(cg == GESTURE_PINCH_IN){
                incrementZoomLevel(); // todo zoom into map and set bounding box accordingly
                msg = "zoomed out";
            } else if(cg == GESTURE_PINCH_OUT){
                decrementZoomLevel(); // todo zoom out
                msg = "zoomed in";
            }
        } else {
            if (GetMouseWheelMove() < 0) {
                decrementZoomLevel();
                msg = "zoomed out";
            }
            else if(GetMouseWheelMove() > 0) {
                incrementZoomLevel();
                msg = "zoomed in";
            }
        }
        addToast(new Toast(msg, 2));
    }
}

void ViewMap::drawOutline() {
    DrawRectangle(6, 6, size.first + 4, size.second + 4, GREEN);
}

void ViewMap::drawControlButtons(Manager *mgr) {
    lockedToTmpPosition = GuiCheckBox(Rectangle{8, 8, 42, 42}, "lck", lockedToTmpPosition); // todo icon button
    // todo add way to easily add named point/line/polygon to postgis database
}

void ViewMap::drawMapInformation() {
    GuiLabel(Rectangle{16, 532, 142, 42}, "z:");
    GuiLabel(Rectangle{42, 532, 142, 42}, std::to_string(zoomLevel).c_str());
}

void ViewMap::show(Manager *mgr) {
    drawOutline();
    drawMap(mgr);
    drawControlButtons(mgr);
    drawMapInformation();
    drawBackButton();
    drawSettingsButton();
    handleTouchStuff(mgr);
    // todo zoom slider; zoom back to default {action} level after {seconds}
    // todo touch move the map; lock button to not snap back after {seconds}
}

void ViewMap::setValuesFalse() {
    viewBackSelected = false;
    viewSettingsSelected = false;
}
