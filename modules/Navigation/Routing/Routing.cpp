//
// Created by nbdy on 28.07.20.
//

#include "Routing.h"
#include "ui_routing.h"


Routing::Routing(QWidget *parent): QWidget(parent), ui(new Ui::Routing){
    ui->setupUi(this);
}

Routing::~Routing() {
    delete ui;
}
