//
// Created by insane on 11.07.20.
//

#include "Navigation.h"
#include "ui_navigation.h"


Navigation::Navigation(QWidget *parent): QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    settings = ISettings::getSettings(this);

    gps = new GPS(this);
    // connect(gps, SIGNAL(onPositionChanged(const QGeoPositionInfo&)), this, SLOT(onPositionChanged(const QGeoPositionInfo&)));

    setDefaultSettings();
    loadSettings();

    setupOSMScout();

    ui->quickWidget->setSource(QUrl("qrc:/main.qml"));
    ui->quickWidget->show();
}

void Navigation::setupOSMScout() {
    osmscout::OSMScoutQt::RegisterQmlTypes();
    osmscout::OSMScoutQtBuilder builder = osmscout::OSMScoutQt::NewInstance();
    builder.WithStyleSheetDirectory("/usr/local/share/stylesheets/")
           .WithStyleSheetFile("/usr/local/share/stylesheets/standard.oss")
           .WithMapLookupDirectories(QStringList() << "/home/insane/maps/");

    if(builder.Init()) scout = &osmscout::OSMScoutQt::GetInstance();
}

Navigation::~Navigation()
{
    osmscout::OSMScoutQt::FreeInstance();
    delete ui;
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

QStringList Navigation::findMapsInDirectory(const QString &directory) {
    QStringList r;
    QDir md(directory);
    for(const QString& d : md.entryList(QDir::Dirs)) r.append(md.absoluteFilePath(d));
    return r;
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