//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_NAVIGATION_H
#define CARPI_QT_NAVIGATION_H

#include "Navigation_global.h"

#include "../../libs/GPS/GPS.h"

#include <QWidget>
#include <QQuickWidget>
#include <QGridLayout>
#include <QQuickPaintedItem>
#include <QQmlEngine>


#include <osmscout/MapWidget.h>

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

    osmscout::OSMScoutQt *scout;

    void buildOSMScout();
    void setDefaultSettings();
    void loadSettings();
    static QStringList findMapsInDirectory(const QString& directory);

public:
    explicit Navigation(QWidget *parent = nullptr);
    ~Navigation() override;
};

extern "C" {
    NAVIGATION_EXPORT int getDefaultIndex();
    NAVIGATION_EXPORT char* getName();
    NAVIGATION_EXPORT QWidget* create();
};


#endif //CARPI_QT_NAVIGATION_H
