//
// Created by nbdy on 28.07.20.
//

#ifndef CARPI_QT_MAP_H
#define CARPI_QT_MAP_H

#include "../../../libs/GPS/GPS.h"

#include <QWidget>
#include <QQmlProperty>

#include <osmscout/OSMScoutQt.h>
#include <osmscout/MapWidget.h>
#include <osmscout/SearchLocationModel.h>
#include <osmscout/RoutingModel.h>
#include <osmscout/AvailableMapsModel.h>
#include <osmscout/MapDownloadsModel.h>
#include <osmscout/Settings.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Map; }
QT_END_NAMESPACE

class Map : public QWidget {
    Q_OBJECT
private:
    Ui::Map *ui;

    void databaseLoaded(osmscout::GeoBox box);
    void setupInitialPosition();

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map() override;
};


#endif //CARPI_QT_MAP_H
