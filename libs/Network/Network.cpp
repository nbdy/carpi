//
// Created by insane on 02.02.19.
//

#include "Network.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <iostream>
#include <sstream>

std::vector<std::string> Network::getNetworkInterfaces() {
    return Utils::listDirectory("/sys/class/net/", false);
}

std::vector<std::string> Network::getWiFiInterfaces() {
    return Utils::findWithPrefix("wl", Network::getNetworkInterfaces());
}

std::vector<std::string> Network::getEthernetInterfaces() {
    return Utils::findWithPrefix("e", Network::getNetworkInterfaces());
}

std::vector<std::string> Network::getEthernetInterfaces(const std::vector<std::string> &lst) {
    return Utils::findWithPrefix("e", lst);
}

std::vector<std::string> Network::getWiFiInterfaces(const std::vector<std::string> &lst) {
    return Utils::findWithPrefix("wl", lst);
}

std::string Network::getInterfaceIP(const std::string& interface) {
    struct ifaddrs *ifaddr, *ifa;
    int family, n;
    char host[NI_MAXHOST];
    if (getifaddrs(&ifaddr) == -1) return "";
    for (ifa = ifaddr, n = 0; ifa != nullptr; ifa = ifa->ifa_next, n++) {
        if (ifa->ifa_addr == nullptr) continue;
        family = ifa->ifa_addr->sa_family;
        if (family == AF_INET && std::string(ifa->ifa_name) == interface) getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
    }
    freeifaddrs(ifaddr);
    return std::string(host);
}

Network::Network() {
    update();
}

void Network::update() {
    interfaces = getNetworkInterfaces();
    wifiInterfaces = getWiFiInterfaces(interfaces);
    ethInterfaces = getEthernetInterfaces(interfaces);
    if(!wifiInterfaces.empty()) wifiInterface = wifiInterfaces[0];
    if(!ethInterfaces.empty()) ethInterface = ethInterfaces[0];
}

std::string Network::getEthInterface() {return ethInterface;}

std::string Network::getWifiInterface() {return wifiInterface;}

void Network::setWifiInterface(std::string interface) {wifiInterface = std::move(interface);}

void Network::setEthInterface(std::string interface) {ethInterface = std::move(interface);}

void Network::setAutomaticUpdate(bool value) {automaticUpdate = value;}

bool Network::getAutomaticUpdate() {return automaticUpdate;}

std::string Network::getIPAddress() {
    return httpGet("http://api.ipify.org");
}

std::vector<std::string> Network::getBluetoothInterfaces() {
    return Utils::listDirectory("/sys/class/bluetooth/", false);
}

std::vector<std::string> Network::getBluetoothInterfaces(const std::vector<std::string> &lst) {
    return Utils::findWithPrefix("hci", lst);
}

bool Network::checkInterfaceUsed(const std::string &interface) {
    return Utils::contains(usedInterfaces, interface);
}

static size_t Network::writeDataToFile(void *ptr, size_t size, size_t nmemb, void *stream){
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

size_t Network::writeDataToString(void *ptr, size_t size, size_t nmemb, void *stream) {
    ((std::string*) stream)->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

int Network::httpGet(std::string url, std::string outfile) {
    CURL *c;
    FILE *o;
    curl_global_init(CURL_GLOBAL_ALL);
    c = curl_easy_init();
    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, writeDataToFile);
    o = fopen(outfile.c_str(), "wb");
    if(o){
        curl_easy_setopt(c, CURLOPT_WRITEDATA, o);
        curl_easy_perform(c);
        fclose(o);
    }
    curl_easy_cleanup(c);
    curl_global_cleanup();
}

std::string Network::httpGet(std::string url) {
    CURL *c;
    std::string r;
    curl_global_init(CURL_GLOBAL_ALL);
    c = curl_easy_init();
    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, writeDataToString);
    curl_easy_setopt(c, CURLOPT_WRITEDATA, &r);
    curl_easy_perform(c);
    curl_easy_cleanup(c);
    curl_global_cleanup();
    return r;
}