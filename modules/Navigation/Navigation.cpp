//
// Created by insane on 11.07.20.
//

#include "Navigation.h"
#include "ui_navigation.h" // todo


Navigation::Navigation(QWidget *parent): QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    settings = ISettings::getSettings(this);
    gps = new GPS(this);
    setDefaultSettings();
    loadSettings();
    buildOSMScout();
    auto *e = new QQmlEngine(this);
    e->setBaseUrl(QUrl("qrc:/qml/main.qml"));
    map_widget = new QQuickWidget(e, this);
}

Navigation::~Navigation()
{
    osmscout::OSMScoutQt::FreeInstance();
    delete ui;
}

void Navigation::buildOSMScout() {
    auto builder = osmscout::OSMScoutQt::NewInstance();
    settings->beginGroup(getName());
    builder.WithStyleSheetDirectory(settings->value(KEY_SETTINGS_STYLE_SHEET_DIRECTORY).toString())
           .WithBasemapLookupDirectory(settings->value(KEY_SETTINGS_MAP_LOOKUP_DIRECTORIES).toString())
           .WithIconDirectory(settings->value(KEY_SETTINGS_ICON_DIRECTORY).toString())
           .WithVoiceProviders(settings->value(KEY_SETTINGS_VOICE_PROVIDERS).toString());
    settings->endGroup();
    if(!builder.Init()) Logger::error(getName(), "could not initialize osmscout"); // todo inform user about errors
}

void Navigation::setDefaultSettings() {
    if(settings->contains(getName())) return;
    settings->beginGroup(getName());
    settings->setValue(KEY_SETTINGS_STYLE_SHEET_DIRECTORY, "");
    settings->endGroup();
}

void Navigation::loadSettings() {
    // todo
}

extern "C" NAVIGATION_EXPORT QWidget* create() {
    return new Navigation();
}

extern "C" NAVIGATION_EXPORT char* getName() {
    return (char*) "Navigation";
}

extern "C" NAVIGATION_EXPORT int getDefaultIndex(){
    return 2;
}