//
// Created by insane on 29.01.19.
//

#ifndef CARPI_MANAGER_H
#define CARPI_MANAGER_H

#include <unistd.h>
#include "../GPS/GPS.h"
#include "../Network/Network.h"
#include "../Configuration/Configuration.h"
//#include "../Navigation/Navigation.h"
#include "../WifiScanner/WifiScanner.h"
#include "../PostgreSQLDB/PostgreSQLDB.h"
#include "../BluetoothScanner/BluetoothScanner.h"

class Manager : public Runnable {
private:
    GPS* gps;
    Network* network;
    PostgreSQLDB* database;
//    Navigation* navigation;
    WifiScanner* wifiScanner;
    BluetoothScanner* bluetoothScanner;

    Configuration* cfg;

    float cpuTemperature;
    time_t bootTime;
    bool isPi;

public:
    explicit Manager(Configuration* cfg);
    Position* getPosition();
    Network* getNetwork();
    PostgreSQLDB* getDatabase();
//    Navigation* getNavigation();
    WifiScanner* getWifiScanner();
    BluetoothScanner* getBluetoothScanner();
    float getCPUTemperature();
    std::string getRunTime();
    bool getIsPi();

    void run() override;
    void stop() override;

    Configuration* getConfiguration();
};


#endif //CARPI_MANAGER_H
