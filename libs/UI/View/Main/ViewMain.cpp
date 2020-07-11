//
// Created by insane on 14.06.20.
//

#include "ViewMain.h"

ViewMain::ViewMain() {
    this->setName("main");
    this->setParent("");
    this->_initSpeedGauge();
}

void ViewMain::_initSpeedGauge() {
    speedGauge = new raygauge::Circle();
    speedGauge->setUnits("km/h");
    speedGauge->setX(50);
    speedGauge->setY(400);
    speedGauge->setDegreesOfCircleUsage(280);
    speedGauge->setOffset(130);
    speedGauge->setMaxValue(240);
}

void ViewMain::drawDashboardGPSValues(Position *position) {
    GuiLabel((Rectangle) {256, 148, 125, 30}, std::to_string(position->getSpeed() * 3600 / 1000).c_str());  // todo set if mph or kmh (currently is kmh)
    GuiLabel((Rectangle) {256, 168, 125, 30}, std::to_string(position->getSatellitesUsed()).c_str());
    GuiLabel((Rectangle) {256, 188, 125, 30}, std::to_string(position->getLongitude()).c_str());
    GuiLabel((Rectangle) {256, 208, 125, 30}, std::to_string(position->getLatitude()).c_str());
    GuiLabel((Rectangle) {256, 228, 125, 30}, std::to_string(position->getAltitude()).c_str());
}

void ViewMain::drawDashboardStatic() {
    GuiLabel((Rectangle) {8, 8, 125, 30}, "overview:");
    GuiLabel((Rectangle) {32, 28, 125, 30}, "network:");
    GuiLabel((Rectangle) {64, 48, 125, 30}, "wifi:");
    GuiLabel((Rectangle) {96, 68, 125, 30}, "ip:");
    GuiLabel((Rectangle) {64, 88, 125, 30}, "ethernet:");
    GuiLabel((Rectangle) {96, 108, 125, 30}, "ip:");
    GuiLabel((Rectangle) {32, 128, 125, 30}, "gps:");
    GuiLabel((Rectangle) {64, 148, 125, 30}, "spd:");
    GuiLabel((Rectangle) {64, 168, 125, 30}, "sats:");
    GuiLabel((Rectangle) {64, 188, 125, 30}, "lng:");
    GuiLabel((Rectangle) {64, 208, 125, 30}, "lat:");
    GuiLabel((Rectangle) {64, 228, 125, 30}, "alt:");
    GuiLabel((Rectangle) {32, 248, 125, 30}, "system:");
    GuiLabel((Rectangle) {64, 268, 125, 30}, "rtime:");
    GuiLabel((Rectangle) {64, 288, 125, 30}, "ctime:");
    GuiLabel((Rectangle) {64, 308, 125, 30}, "cpu temp:");
    mainMenuSelected = GuiButton((Rectangle) {592, 492, 200, 100}, "main menu");
}

void ViewMain::drawDashboardNetworkValues(Network *network) {
    bool hasIP = false;
    std::string wifiInterface = network->getWifiInterface();
    std::string ethInterface = network->getEthInterface();
    if(wifiInterface.empty() && ethInterface.empty()) GuiLabel((Rectangle) {256, 28, 125, 30}, "no interfaces");
    if(!wifiInterface.empty()) {
        std::string ip = network->getInterfaceIP(wifiInterface);
        GuiLabel((Rectangle) {256, 48, 125, 30}, wifiInterface.c_str());
        if(!ip.empty()) {GuiLabel((Rectangle) {256, 68, 125, 30}, ip.c_str()); hasIP = true;}
    }
    if(!ethInterface.empty()){
        std::string ip = network->getInterfaceIP(ethInterface);
        GuiLabel((Rectangle) {256, 88, 125, 30}, ethInterface.c_str());
        if(!ip.empty()) {GuiLabel((Rectangle) {256, 108, 125, 30}, ip.c_str()); hasIP = true;}
    }
    if(hasIP) GuiLabel((Rectangle) {256, 28, 125, 30}, "connected");
    else GuiLabel((Rectangle) {256, 28, 125, 30}, "disconnected");
}

void ViewMain::drawDashboardSystemValues(Manager *mgr) {
    GuiLabel((Rectangle) {256, 268, 125, 30}, mgr->getRunTime().c_str());
    GuiLabel((Rectangle) {256, 288, 125, 30}, Utils::getCurrentTime().c_str());
    std::string tmp = std::to_string(mgr->getCPUTemperature()).substr(0, 5) + " °C";
    GuiLabel((Rectangle) {256, 308, 125, 30}, tmp.c_str());
}

void ViewMain::drawSpeedGauge(Manager *mgr) {
    speedGauge->setColor(GetColor(mgr->getConfiguration()->getStyleConfiguration().textColorNormal));
    speedGauge->setValue(std::to_string((int) mgr->getPosition()->getSpeed()));
    speedGauge->draw();
}

void ViewMain::show(Manager *mgr) {
    drawDashboardStatic();
    drawDashboardGPSValues(mgr->getPosition());
    drawDashboardNetworkValues(mgr->getNetwork());
    drawDashboardSystemValues(mgr);
    drawSpeedGauge(mgr);
}

std::string ViewMain::getNextView() {
    if(mainMenuSelected) return "main menu";
    else return "main";
}

void ViewMain::setValuesFalse() {
    mainMenuSelected = false;
}
