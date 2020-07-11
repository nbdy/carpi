//
// Created by nbdy on 11.06.20.
//

#include "ViewManager.h"
#include "../View/Main/ViewMain.h"
#include "../View/MainMenu/ViewMainMenu.h"
#include "../View/Updater/ViewUpdater.h"
#include "../View/Audio/ViewAudio.h"
#include "../View/MusicPlayer/Aux/ViewAuxMusicPlayer.h"
#include "../View/MusicPlayer/Radio/ViewRadioMusicPlayer.h"
#include "../View/Wireless/ViewWireless.h"
#include "../View/Wireless/Bluetooth/ViewWirelessBluetooth.h"
#include "../View/Wireless/WiFi/ViewWirelessWiFi.h"
#include "../View/Wireless/HackRF/ViewWirelessHackRF.h"
#include "../View/Settings/ViewSettings.h"
#include "../View/Settings/GPS/ViewSettingsGPS.h"
#include "../View/Settings/Audio/ViewSettingsAudio.h"
#include "../View/Settings/Audio/Aux/ViewSettingsAudioAux.h"
#include "../View/Settings/Audio/Radio/ViewSettingsAudioRadio.h"
#include "../View/Settings/Audio/Library/ViewSettingsAudioLibrary.h"
#include "../View/Settings/Wireless/ViewSettingsWireless.h"
#include "../View/Settings/Wireless/Bluetooth/ViewSettingsWirelessBluetooth.h"
#include "../View/Settings/Wireless/HackRF/ViewSettingsWirelessHackRF.h"
#include "../View/Settings/UI/ViewSettingsUI.h"
#include "../View/Settings/Map/ViewSettingsMap.h"
#include "../View/Settings/Map/Cache/ViewSettingsMapCache.h"
#include "../View/Settings/Map/Download/ViewSettingsMapDownload.h"
#include "../View/Settings/Updater/ViewSettingsUpdater.h"
#include "../View/Settings/FileManager/ViewSettingsFileManager.h"
#include "../View/Settings/System/ViewSettingsSystem.h"
#include "../View/Map/ViewMap.h"
#include "../View/FileManager/ViewFileManager.h"
#include "../View/Settings/Wireless/WiFi/ViewSettingsWirelessWiFi.h"

void ViewManager::buildUI() {
    // main
    views.emplace_back(new ViewMain());
    // main menu
    views.emplace_back(new ViewMainMenu());
    // updater
    views.emplace_back(new ViewUpdater());
    // audio
    views.emplace_back(new ViewAudio());
    views.emplace_back(new ViewAuxMusicPlayer());
    views.emplace_back(new ViewRadioMusicPlayer());
    // wireless
    views.emplace_back(new ViewWireless());
    views.emplace_back(new ViewWirelessBluetooth());
    views.emplace_back(new ViewWirelessWiFi());
    views.emplace_back(new ViewWirelessHackRF());
    // settings
    views.emplace_back(new ViewSettings());
    views.emplace_back(new ViewSettingsGPS());
    views.emplace_back(new ViewSettingsAudio());
    views.emplace_back(new ViewSettingsAudioAux());
    views.emplace_back(new ViewSettingsAudioRadio());
    views.emplace_back(new ViewSettingsAudioLibrary(keyboard));
    views.emplace_back(new ViewSettingsWireless());
    views.emplace_back(new ViewSettingsWirelessWiFi());
    views.emplace_back(new ViewSettingsWirelessBluetooth());
    views.emplace_back(new ViewSettingsWirelessHackRF());
    views.emplace_back(new ViewSettingsUI());
    views.emplace_back(new ViewSettingsMap());
    views.emplace_back(new ViewSettingsMapCache(keyboard));
    views.emplace_back(new ViewSettingsMapDownload());
    views.emplace_back(new ViewSettingsUpdater(keyboard));
    views.emplace_back(new ViewSettingsFileManager());
    views.emplace_back(new ViewSettingsSystem());
    // map
    views.emplace_back(new ViewMap());
    // file manager
    views.emplace_back(new ViewFileManager());
}

ViewManager::ViewManager(Manager *mgr) {
    currentView = "main";
    keyboard = new KeyboardLayout();
    widgetManager = new WidgetManager();
    toastManager = new ToastManager();
    sidebar = new Sidebar(mgr);
    buildUI();
}

View *ViewManager::getCurrentView() {
    for(View* v : views) if(v->getName() == currentView) return v;
    return nullptr;
}

void ViewManager::setValuesFalse() {
    for(View* v : views)v->setValuesFalse();
}

void ViewManager::loop(Manager *mgr) {
    View* v = getCurrentView();
    v->show(mgr);
    sidebar->show();
    toastManager->addToasts(v->getToasts());
    toastManager->loop();
    currentView = getCurrentView()->getNextView();
    widgetManager->show(mgr);
    setValuesFalse();
}
