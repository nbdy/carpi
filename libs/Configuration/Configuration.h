//
// Created by insane on 02.02.19.
//

#ifndef CARPI_CONFIGURATION_H
#define CARPI_CONFIGURATION_H


#include <string>
#include "../Json/json.hpp"
#include "../Utils/Utils.h"
#include "../GPS/GPS.h"


using namespace nlohmann;

namespace sc {
    struct StyleConfiguration {
        int borderColorNormal;
        int baseColorNormal;
        int textColorNormal;
        int borderColorFocused;
        int baseColorFocused;
        int textColorFocused;
        int borderColorPressed;
        int baseColorPressed;
        int textColorPressed;
        int borderColorDisabled;
        int baseColorDisabled;
        int textColorDisabled;

        int borderWidth;
        int innerPadding;
        int textSize;
        int textSpacing;
        int lineColor;
        int backGroundColor;
    };


    inline void to_json(json& j, const sc::StyleConfiguration& sc){
        j = json{
            {"borderColorNormal", Utils::colorBase162Str(sc.borderColorNormal)}, {"baseColorNormal", Utils::colorBase162Str(sc.baseColorNormal)}, {"textColorNormal", Utils::colorBase162Str(sc.textColorNormal)},
            {"borderColorFocused", Utils::colorBase162Str(sc.borderColorFocused)}, {"baseColorFocused", Utils::colorBase162Str(sc.baseColorFocused)}, {"textColorFocused", Utils::colorBase162Str(sc.textColorFocused)},
            {"borderColorPressed", Utils::colorBase162Str(sc.borderColorPressed)}, {"baseColorPressed", Utils::colorBase162Str(sc.baseColorPressed)}, {"textColorPressed", Utils::colorBase162Str(sc.textColorPressed)},
            {"borderColorDisabled", Utils::colorBase162Str(sc.borderColorDisabled)}, {"baseColorDisabled", Utils::colorBase162Str(sc.baseColorDisabled)}, {"textColorDisabled", Utils::colorBase162Str(sc.textColorDisabled)},
            {"borderWidth", sc.borderWidth}, {"innerPadding", sc.innerPadding}, {"textSize", sc.textSize}, {"textSpacing", sc.textSpacing},
            {"lineColor", Utils::colorBase162Str(sc.lineColor)}, {"backgroundColor", Utils::colorBase162Str(sc.backGroundColor)}
        };
    }

    inline void from_json(const json& j, sc::StyleConfiguration& sc){
        // normal
        sc.borderColorNormal = Utils::colorStr2Base16(j.at("borderColorNormal"));
        sc.baseColorNormal = Utils::colorStr2Base16(j.at("baseColorNormal"));
        sc.textColorNormal = Utils::colorStr2Base16(j.at("textColorNormal"));
        // focused
        sc.borderColorFocused = Utils::colorStr2Base16(j.at("borderColorFocused"));
        sc.baseColorFocused = Utils::colorStr2Base16(j.at("baseColorFocused"));
        sc.textColorFocused = Utils::colorStr2Base16(j.at("textColorFocused"));
        // pressed
        sc.borderColorPressed = Utils::colorStr2Base16(j.at("borderColorPressed"));
        sc.baseColorPressed = Utils::colorStr2Base16(j.at("baseColorPressed"));
        sc.textColorPressed = Utils::colorStr2Base16(j.at("textColorPressed"));
        // disabled
        sc.borderColorDisabled = Utils::colorStr2Base16(j.at("borderColorDisabled"));
        sc.baseColorDisabled = Utils::colorStr2Base16(j.at("baseColorDisabled"));
        sc.textColorDisabled = Utils::colorStr2Base16(j.at("textColorDisabled"));
        // other
        sc.borderWidth = j.at("borderWidth");
        sc.innerPadding = j.at("innerPadding");
        sc.textSize = j.at("textSize");
        sc.textSpacing = j.at("textSpacing");
        sc.lineColor = Utils::colorStr2Base16(j.at("lineColor"));
        sc.backGroundColor = Utils::colorStr2Base16(j.at("backgroundColor"));
    }
}

namespace mc {
    struct MusicConfiguration {
        bool playing; // autoplay on boot and icon control
        std::string path;
        int dontRepeatThreshold; // should be less than the songs you have
    };

    inline void to_json(json& j, const mc::MusicConfiguration& mc){
        j = json{{"path", mc.path}, {"playing", mc.playing}, {"dontRepeatThreshold", mc.dontRepeatThreshold}};
    }

    inline void from_json(const json& j, mc::MusicConfiguration& mc){
        mc.path = j.at("path");
        mc.playing = j.at("playing");
        mc.dontRepeatThreshold = j.at("dontRepeatThreshold");
    }
}

namespace rc {
    struct RadioConfiguration {
        float freq;
    };

    inline void to_json(json& j, const rc::RadioConfiguration& rc){
        j = json{{"freq", rc.freq}, {}, {}};
    }

    inline void from_json(const json& j, rc::RadioConfiguration& rc){
        rc.freq = j.at("freq");
    }
}

namespace wc {
    struct WifiConfiguration {
        bool enabled;
        std::vector<std::string> interfaces;
    };

    inline void to_json(json& j, const wc::WifiConfiguration& wc){
        j = json{{"interfaces", wc.interfaces}, {"enabled", wc.enabled}, {}};
    }

    inline void from_json(const json& j, wc::WifiConfiguration& wc){
        j.at("interfaces").get_to(wc.interfaces);
        j.at("enabled").get_to(wc.enabled);
    }
}

namespace bc {
    struct BluetoothConfiguration {
        bool enabled;
        std::vector<std::string> interfaces;
    };

    inline void to_json(json& j, const bc::BluetoothConfiguration& bc){
        j = json{{"interfaces", bc.interfaces}, {"enabled", bc.enabled}, {}};
    }

    inline void from_json(const json& j, bc::BluetoothConfiguration& bc){
        j.at("interfaces").get_to(bc.interfaces);
        j.at("enabled").get_to(bc.enabled);
    }
}

namespace nc {
    struct NavigationConfiguration {
        std::string provider;
        std::string infile;
        std::string cacheDirectory;
        std::vector<int> tileResolution;
        json mapDownloads;
    };

    inline void to_json(json& j, const nc::NavigationConfiguration& nc){
        j = json{{"infile", nc.infile}, {"cacheDirectory", nc.cacheDirectory}, {"tileResolution", nc.tileResolution}, {"mapDownloads", nc.mapDownloads}, {"provider", nc.provider}};
    }

    inline void from_json(const json& j, nc::NavigationConfiguration& nc){
        nc.cacheDirectory = j.at("cacheDirectory");
        nc.infile = j.at("infile");
        j.at("tileResolution").get_to(nc.tileResolution);
        nc.mapDownloads = j.at("mapDownloads");
        nc.provider = j.at("provider");
    }
}

namespace uc {
    struct UpdaterConfiguration {
        std::string path;
        std::string url;
        bool onBoot;
    };

    inline void to_json(json& j, const uc::UpdaterConfiguration& uc){
        j = json{{"url", uc.url}, {"onBoot", uc.onBoot}, {"path", uc.path}};
    }

    inline void from_json(const json& j, uc::UpdaterConfiguration& uc){
        uc.url = j.at("url");
        uc.onBoot = j.at("onBoot");
        uc.path = j.at("path");
    }
}

namespace db {
    struct DatabaseConfiguration {
        std::string host;
        int port;
        std::string dbname;
        std::string username;
        std::string password;
    };

    inline void to_json(json& j, const db::DatabaseConfiguration& d){
        j = json{{"host", d.host}, {"port", d.port}, {"dbname", d.dbname}, {"username", d.username}, {"password", d.password}};
    }

    inline void from_json(const json& j, db::DatabaseConfiguration& d){
        d.host = j.at("host");
        d.port = j.at("port");
        d.dbname = j.at("dbname");
        d.username = j.at("username");
        d.password = j.at("password");
    }
}

namespace gc {
    struct GPSConfiguration {
        bool enabled;
        json defaultCoordinate;
    };

    inline void to_json(json& j, const gc::GPSConfiguration& g){
        j = json{{"enabled", g.enabled}, {"defaultCoordinate", g.defaultCoordinate}, {}};
    }

    inline void from_json(const json& j, gc::GPSConfiguration& g){
        g.enabled = j.at("enabled");
        g.defaultCoordinate = j.at("defaultCoordinate");
    }
}

class Configuration {
private:
    json config;
    std::string fileName;

public:
    Configuration();

    void dump();
    void dump(const std::string& filename);
    static Configuration* load(const std::string& filename);
    static Configuration* load();

    sc::StyleConfiguration getStyleConfiguration();
    mc::MusicConfiguration getMusicConfiguration();
    rc::RadioConfiguration getRadioConfiguration();
    db::DatabaseConfiguration getDatabaseConfiguration();
    wc::WifiConfiguration getWirelessConfiguration();
    bc::BluetoothConfiguration getBluetoothConfiguration();
    nc::NavigationConfiguration getNavigationConfiguration();
    uc::UpdaterConfiguration getUpdaterConfiguration();
    gc::GPSConfiguration getGPSConfiguration();

    Position* getDefaultPosition();

    void setValue(const std::string& cfgKey, const std::string& key, const std::string& value);

    void setGPSEnabled();
    void setGPSDisabled();
    void setSpeedsterEnabled();
    void setSpeedsterDisabled();
    void setOnBootUpdater(bool value);
    void setOnBootUpdaterEnabled();
    void setOnBootUpdaterDisabled();
    void setProjectUrl(const std::string& value);
    void setMusicLibraryPath(const std::string& value);
    void setBluetoothDisabled();
    void setWifiDisabled();
    void setBluetoothEnabled();
    void setWifiEnabled();
    void setCacheDirectory(const std::string& value);
};

#endif //CARPI_CONFIGURATION_H
