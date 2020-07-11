//
// Created by nbdy on 11.06.20.
//

#include <raylib.h>
#include "Sidebar.h"
#include "../../../raycons/Icons.h"

void Sidebar::show() {
    DrawRectangle(posX, posY, sizeX, sizeY, GREEN);
    DrawRectangle(posX + 2, posY + 2, sizeX - 4, sizeY - 4, BLACK);
    DrawRectangle(posX, posY, sizePuller, sizeY, GREEN);
    DrawRectangle(posX + 4, posY + 4, sizePuller - 8, sizeY - 8, BLACK);
    int pM = (sizePuller - 12) / 2;
    int pX = posX + pM;

    int bottom = 340;
    Configuration* cfg = mgr->getConfiguration();
    if(cfg->getBluetoothConfiguration().enabled) { Icons::bluetoothEnabled(pX, posY + bottom, 12, 12); bottom -= 24;}
    else {Icons::bluetoothDisabled(pX , posY + bottom, 12, 12); bottom -= 24;}
    if(cfg->getWirelessConfiguration().enabled) {Icons::wifiEnabled(pX, posY + bottom, 12, 12); bottom -= 20;}
    else {Icons::wifiDisabled(pX, posY + bottom, 12, 12); bottom -= 20;}
    if(cfg->getMusicConfiguration().playing) {Icons::play(pX, posY + bottom, 12, 12); bottom -= 20;}
    else {Icons::pause(pX, posY + bottom, 12, 12); bottom -= 24;}
    if(cfg->getGPSConfiguration().enabled) {
        if(mgr->getPosition()->empty()){ Icons::gpsUnFixed(pX, posY + bottom, 12, 12); bottom -= 24; }
        else {Icons::gpsFixed(pX, posY + bottom, 12, 12); bottom -= 24;}
    }
    else{Icons::gpsUnFixed(pX, posY + bottom, 12, 12); bottom -= 24;}

    Vector2 tPos = {0, 0};

    if(mgr->getIsPi()) tPos = GetTouchPosition(0);
    else { if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) tPos = GetMousePosition(); }

    if((float) posX <= lockPositionX2) {
        // todo algorithm every x icons increment ps
        auto homeShortCutX = (float) (posX + sizePuller + 8);
        auto homeShortCutY = (float) (posY + 8);
        Icons::home((int) (homeShortCutX + 4), (int) (homeShortCutY + 4), 32, 32);
        if(tPos.x >= homeShortCutX && tPos.x <= homeShortCutX + 18 && tPos.y >= homeShortCutY && tPos.y <= homeShortCutY + 18) {
            std::cout << "go home" << std::endl;
            // todo go to homescreen / do not show on homescreen
        }

        float musicPlayerShortCutX = homeShortCutX + 54;
        float musicPlayerShortCutY = homeShortCutY;
        Icons::album((int) (musicPlayerShortCutX + 12), (int) (musicPlayerShortCutY + 12), 16, 16);
        if(tPos.x >= musicPlayerShortCutX && tPos.x <= musicPlayerShortCutX + 18 && tPos.y >= musicPlayerShortCutY && tPos.y <= musicPlayerShortCutY + 18){
            std::cout << "go music player" << std::endl;

        }
    } // todo more shortcuts / shortcut scrollbar / make shortcut order appearance editable

    bool wasTouchedLast = (tPos.y >= (float) posY && tPos.y <= (float) (posY + sizeY) &&
                           tPos.x >= (float) posX && tPos.x <= (float) (posX + sizePuller));

    if(wasTouchedLast) {
        posX = (int) tPos.x - sizePuller / 2;
    } else {
        if((float) posX < lockPositionX1) posX = (int) lockPositionX1;
        else if((float) posX > lockPositionX1 && (float) posX <= lockPositionX2) posX = (int) lockPositionX2;
        else if((float) posX > lockPositionX2) posX = (int) basePositionX;
    }

    // todo first stage icons / settings when long tap
    // todo second stage like first but also top x running apps
    // todo third stage like second but also top x most used apps
}

Sidebar::Sidebar(Manager *mgr) {
    this->mgr = mgr;
}
