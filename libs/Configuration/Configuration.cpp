//
// Created by insane on 02.02.19.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include "Configuration.h"


Configuration::Configuration() {

}

void Configuration::dump(const std::string &filename) {
    std::ofstream o(fileName);
    o << std::setw(4) << config << std::endl;
}

void Configuration::dump() {
    std::ofstream o(fileName);
    o << std::setw(4) << config << std::endl;
}

Configuration* Configuration::load(const std::string &filename) {
    if(!Utils::isFile(filename)) return nullptr;
    auto cfg = new Configuration();
    std::ifstream i(filename);
    cfg->fileName = filename;
    i >> cfg->config;
    return cfg;
}

Configuration* Configuration::load() {
    auto cfg = new Configuration();
    if(Utils::isFile("/etc/carpi/config.json")) cfg->fileName = "/etc/carpi/config.json";
    else if(Utils::isFile("config.json")) cfg->fileName = "config.json";
    else if(Utils::isFile("../config.json")) cfg->fileName = "../config.json";
    if(cfg->fileName.empty()) return nullptr;
    std::cout << "loading: " << cfg->fileName << std::endl;
    std::ifstream i(cfg->fileName);
    i >> cfg->config;
    // std::cout << cfg->config << std::endl;
    return cfg;
}

sc::StyleConfiguration Configuration::getStyleConfiguration() {
    return config["style"].get<sc::StyleConfiguration>();
}

mc::MusicConfiguration Configuration::getMusicConfiguration() {
    return config["music"].get<mc::MusicConfiguration>();
}

rc::RadioConfiguration Configuration::getRadioConfiguration() {
    return config["radio"].get<rc::RadioConfiguration>();
}

wc::WifiConfiguration Configuration::getWirelessConfiguration() {
    return config["wifi"].get<wc::WifiConfiguration>();
}

bc::BluetoothConfiguration Configuration::getBluetoothConfiguration() {
    return config["bluetooth"].get<bc::BluetoothConfiguration>();
}

nc::NavigationConfiguration Configuration::getNavigationConfiguration() {
    return config["navigation"].get<nc::NavigationConfiguration>();
}

void Configuration::setSpeedsterEnabled() {
    config["navigation"]["enableSpeedster"] = true;
}

void Configuration::setSpeedsterDisabled() {
    config["navigation"]["enableSpeedster"] = false;
}

uc::UpdaterConfiguration Configuration::getUpdaterConfiguration() {
    return config["updater"].get<uc::UpdaterConfiguration>();
}

void Configuration::setOnBootUpdaterEnabled() {
    config["updater"]["onBoot"] = true;
}

void Configuration::setOnBootUpdaterDisabled() {
    config["updater"]["onBoot"] = false;
}

void Configuration::setOnBootUpdater(bool value) {
    config["updater"]["onBoot"] = value;
}

db::DatabaseConfiguration Configuration::getDatabaseConfiguration() {
    return config["database"].get<db::DatabaseConfiguration>();
}

void Configuration::setProjectUrl(const std::string &value) {config["updater"]["url"] = value;}

void Configuration::setMusicLibraryPath(const std::string &value) {config["music"]["path"] = value;}

void Configuration::setBluetoothDisabled() {
    config["bluetooth"]["enabled"] = false;
}

void Configuration::setBluetoothEnabled() {
    config["bluetooth"]["enabled"] = true;
}

void Configuration::setWifiDisabled() {
    config["wifi"]["enabled"] = false;
}

void Configuration::setWifiEnabled() {
    config["wifi"]["enabled"] = true;
}

void Configuration::setGPSDisabled() {
    config["gps"]["enabled"] = false;
}

void Configuration::setGPSEnabled() {
    config["gps"]["enabled"] = true;
}

gc::GPSConfiguration Configuration::getGPSConfiguration() {
    return config["gps"].get<gc::GPSConfiguration>();
}

void Configuration::setCacheDirectory(const std::string &value) {config["navigation"]["cacheDirectory"] = value;}

void Configuration::setValue(const std::string &cfgKey, const std::string &key, const std::string &value) {
    config[cfgKey][key] = value;
}

Position* Configuration::getDefaultPosition() {
    Position *r = new Position();
    r->setLatitude(config["gps"]["defaultCoordinate"]["latitude"]);
    r->setLongitude(config["gps"]["defaultCoordinate"]["longitude"]);
    r->setAltitude(0);
    r->setSpeed(0);
    r->setSatellitesUsed(42);
    return r;
}