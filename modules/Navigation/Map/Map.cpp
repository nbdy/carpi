//
// Created by nbdy on 28.07.20.
//

#include "Map.h"
#include "ui_map.h"

Map::Map(QWidget *parent): QWidget(parent), ui(new Ui::Map) {
    ui->setupUi(this);

    ui->map->setSource(QUrl("qrc:/Map/qml/main.qml"));
    ui->map->show();
}

Map::~Map() {
    delete ui;
}