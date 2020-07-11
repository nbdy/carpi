//
// Created by insane on 29.01.19.
//

#include <sstream>
#include <iomanip>
#include "Manager.h"

Manager::Manager(Configuration* cfg) {
    this->cfg = cfg;
    isPi = Utils::isPi();
    time(&bootTime);
    gps = new GPS(this->cfg->getDefaultPosition());
    network = new Network();
    database = new PostgreSQLDB(cfg->getDatabaseConfiguration());
    wifiScanner = new WifiScanner(network);
    bluetoothScanner = new BluetoothScanner();
    navigation = new Navigation(cfg->getNavigationConfiguration());
    setDoRun(true);
}

Position* Manager::getPosition() {
    return gps->getPosition();
}

void Manager::run() {
    std::thread gpsThread = gps->getThread();
    gpsThread.detach();

    while(this->getDoRun()){
        if(network->getAutomaticUpdate()) network->update();
        cpuTemperature = Utils::getCPUTemp();
        usleep(420);
    }

    gps->stop();
}

void Manager::stop() {
    this->gps->stop();
    this->setDoRun(false);
}

Network* Manager::getNetwork() {
    return network;
}

Configuration* Manager::getConfiguration() {
    return cfg;
}

Navigation* Manager::getNavigation() {return navigation;}

WifiScanner* Manager::getWifiScanner() {return wifiScanner;}

PostgreSQLDB* Manager::getDatabase() {return database;}

float Manager::getCPUTemperature() {return cpuTemperature;}

std::string Manager::getRunTime() {
    time_t cT = time(nullptr);
    time_t rT = cT - bootTime;
    char b[20];
    strftime(b, 20, "%d %H:%M:%S", localtime(&rT));
    return std::string(b);
}

bool Manager::getIsPi() {return isPi;}

BluetoothScanner* Manager::getBluetoothScanner() { return bluetoothScanner; }