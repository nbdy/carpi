//
// Created by insane on 11.07.20.
//

#include "WiFi.h"
#include "ui_wifi.h"


WiFi::WiFi(QWidget *parent): QMainWindow(parent), ui(new Ui::WiFi)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

WiFi::~WiFi()
{
    delete ui;
}

extern "C" WIFI_EXPORT QWidget* render() {
    return new WiFi();
}

extern "C" WIFI_EXPORT QString getName() {
    return "WiFi";
}