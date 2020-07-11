//
// Created by insane on 02.02.19.
//

#ifndef CARPI_NETWORK_H
#define CARPI_NETWORK_H

#include <string>
#include <vector>

#include <curl/curl.h>
#include <curl/easy.h>
#include "../Utils/Utils.h"

class Network {
private:
    std::string wifiInterface;
    std::string ethInterface;

    std::vector<std::string> wifiInterfaces;
    std::vector<std::string> ethInterfaces;
    std::vector<std::string> interfaces;

    std::vector<std::string> usedInterfaces;

    bool automaticUpdate = false;

public:
    static std::vector<std::string> getNetworkInterfaces();
    static std::vector<std::string> getWiFiInterfaces();
    static std::vector<std::string> getWiFiInterfaces(const std::vector<std::string>& lst);

    static std::vector<std::string> getEthernetInterfaces();
    static std::vector<std::string> getEthernetInterfaces(const std::vector<std::string>& lst);

    static std::vector<std::string> getBluetoothInterfaces();
    static std::vector<std::string> getBluetoothInterfaces(const std::vector<std::string>& lst);

    std::string getInterfaceIP(const std::string& interface);

    bool checkInterfaceUsed(const std::string &interface);

    Network();
    void update();

    void setWifiInterface(std::string interface);
    void setEthInterface(std::string interface);

    std::string getWifiInterface();
    std::string getEthInterface();

    bool getAutomaticUpdate();
    void setAutomaticUpdate(bool value);

    std::string getIPAddress();

    static size_t writeDataToFile(void *ptr, size_t size, size_t nmemb, void *stream);
    static size_t writeDataToString(void *ptr, size_t size, size_t nmemb, void *stream);

    static int httpGet(std::string url, std::string outfile);
    static std::string httpGet(std::string url);
};


#endif //CARPI_NETWORK_H
