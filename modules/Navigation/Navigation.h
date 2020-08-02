//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_ROUTING_H
#define CARPI_QT_NAVIGATION_H

#include "Navigation_global.h"

#include "../../libs/GPS/GPS.h"
#include "Map/Map.h"
#include "Routing/Routing.h"

#include <QDir>
#include <QWidget>
#include <QGridLayout>

#include <osmscout/OSMScoutQt.h>
#include <osmscout/MapWidget.h>
#include <osmscout/SearchLocationModel.h>
#include <osmscout/RoutingModel.h>
#include <osmscout/AvailableMapsModel.h>
#include <osmscout/MapDownloadsModel.h>
#include <osmscout/Settings.h>

#define KEY_SETTINGS_STYLE_SHEET_DIRECTORY "stylesDirectory"
#define KEY_SETTINGS_ICON_DIRECTORY "iconsDirectory"
#define KEY_SETTINGS_MAP_LOOKUP_DIRECTORIES "mapLookupDirectories"
#define KEY_SETTINGS_VOICE_PROVIDERS "voiceProviders"

QT_BEGIN_NAMESPACE
namespace Ui { class Navigation; }
QT_END_NAMESPACE

class Navigation : public QWidget
{
Q_OBJECT
private:
    Ui::Navigation *ui;
    QSettings *settings;
    GPS *gps;

    Map *map;
    Routing *routing;

    QGridLayout *mapLayout;
    QGridLayout *routingLayout;

    osmscout::OSMScoutQt *scout;

    void setupOSMScout();
    static QStringList findMapsInDirectory(const QString &directory);

    void setDefaultSettings();
    void loadSettings();

public:
    explicit Navigation(QWidget *parent = nullptr);
    ~Navigation() override;
};

extern "C" {
    NAVIGATION_EXPORT int getDefaultIndex();
    NAVIGATION_EXPORT char* getName();
    NAVIGATION_EXPORT QWidget* create();
    NAVIGATION_EXPORT QStringList* getSettingsKeys();
};


#endif //CARPI_QT_ROUTING_H
