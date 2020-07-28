//
// Created by insane on 11.07.20.
//

#include "Navigation.h"
#include "ui_navigation.h"


Navigation::Navigation(QWidget *parent): QWidget(parent), ui(new Ui::Navigation) {
    ui->setupUi(this);
    settings = ISettings::getSettings(this);

    gps = new GPS(this);
    setupOSMScout();
    // connect(gps, SIGNAL(onPositionChanged(const QGeoPositionInfo&)), this, SLOT(onPositionChanged(const QGeoPositionInfo&)));

    map = new Map();
    navigation = new Navigation();

    setDefaultSettings();
    loadSettings();
}

Navigation::~Navigation()
{
    osmscout::OSMScoutQt::FreeInstance();
    delete ui;
}

void Navigation::setupOSMScout() {
    osmscout::OSMScoutQt::RegisterQmlTypes();
    osmscout::OSMScoutQtBuilder builder = osmscout::OSMScoutQt::NewInstance();
    builder.WithStyleSheetDirectory("/usr/local/share/stylesheets/")
            .WithStyleSheetFile("/usr/local/share/stylesheets/standard.oss")
            .WithMapLookupDirectories(findMapsInDirectory("/media/data/map/"));

    if(builder.Init()) scout = &osmscout::OSMScoutQt::GetInstance();
}

QStringList Navigation::findMapsInDirectory(const QString &directory) {
    QStringList r;
    QDir md(directory);
    for(const QString& d : md.entryList(QDir::Dirs)) r.append(md.absoluteFilePath(d));
    return r;
}

void Navigation::setDefaultSettings() {
    if(settings->contains(getName())) return;
    Logger::debug(getName(), "setting default settings");
    settings->beginGroup(getName());
    settings->setValue(KEY_SETTINGS_STYLE_SHEET_DIRECTORY, "/var/lib/carpi/stylesheets/");
    settings->setValue(KEY_SETTINGS_ICON_DIRECTORY, "/var/lib/carpi/icons/");
    settings->setValue(KEY_SETTINGS_MAP_LOOKUP_DIRECTORIES, "/var/lib/carpi/maps/");
    settings->setValue(KEY_SETTINGS_VOICE_PROVIDERS, "/var/lib/carpi/providers/voice.json");
    settings->endGroup();
}

void Navigation::loadSettings() {
    // todo
}

extern "C" NAVIGATION_EXPORT QWidget* create() {
    return new Navigation();
}

extern "C" NAVIGATION_EXPORT char* getName() {
    return (char*) "Routing";
}

extern "C" NAVIGATION_EXPORT int getDefaultIndex(){
    return 2;
}

extern "C" NAVIGATION_EXPORT QStringList *getSettingsKeys(){
    auto r = new QStringList();
    r->append(KEY_SETTINGS_STYLE_SHEET_DIRECTORY);
    r->append(KEY_SETTINGS_VOICE_PROVIDERS);
    r->append(KEY_SETTINGS_ICON_DIRECTORY);
    r->append(KEY_SETTINGS_MAP_LOOKUP_DIRECTORIES);
    return r;
}