//
// Created by insane on 11.07.20.
//

#include "SystemInfo.h"
#include "ui_systeminfo.h"

#include "../../libs/Network/Network.h"


SystemInfo::SystemInfo(QWidget *parent): QWidget(parent), ui(new Ui::SystemInfo)
{
    ui->setupUi(this);

    //ui->wifi_mac->setText(Network::getMAC("wl"));
    //ui->eth_mac->setText(Network::getMAC("eth"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(840);
}

SystemInfo::~SystemInfo()
{
    timer->stop();
    delete ui;
    delete timer;
}

void SystemInfo::timerSlot() {

}

extern "C" SYSTEMINFO_EXPORT QWidget* render() {
    return new SystemInfo();
}

extern "C" SYSTEMINFO_EXPORT char* getName() {
    return (char*) "SystemInfo";
}



