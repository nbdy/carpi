//
// Created by nbdy on 28.07.20.
//

#include "Map.h"
#include "ui_map.h"

Map::Map(QWidget *parent): QWidget(parent), ui(new Ui::Map) {
    ui->setupUi(this);

    ui->map->setSource(QUrl("qrc:/Map/qml/main.qml"));
    ui->map->show();

    auto *mw = qobject_cast<osmscout::MapWidget*>(ui->map->rootObject()->findChild<QQuickItem*>("map"));
    connect(mw, &osmscout::MapWidget::databaseLoaded, this, &Map::databaseLoaded);
}

Map::~Map() {
    delete ui;
}

void Map::databaseLoaded(osmscout::GeoBox box) {
    Logger::debug("Map", QString::fromStdString(box.GetDisplayText()));
}
