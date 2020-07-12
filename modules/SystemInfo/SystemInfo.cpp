//
// Created by insane on 11.07.20.
//

#include "SystemInfo.h"
#include "ui_systeminfo.h"

#include "../../libs/Network/Network.h"
#include "../../libs/Utils/Utils.h"


SystemInfo::SystemInfo(QWidget *parent): QWidget(parent), ui(new Ui::SystemInfo)
{
    ui->setupUi(this);

    ui->wifi_mac->setText(Network::getMAC("wl"));
    ui->eth_mac->setText(Network::getMAC("eth"));

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
    ui->wifi_ip->setText(Network::getIP("wl"));
    ui->eth_ip->setText(Network::getIP("eth"));
    ui->cpu_temp->setText(QString::number(Utils::getCPUTemp()) + " °C");
}

extern "C" SYSTEMINFO_EXPORT QWidget* render() {
    return new SystemInfo();
}

extern "C" SYSTEMINFO_EXPORT char* getName() {
    return (char*) "SystemInfo";
}

extern "C" SYSTEMINFO_EXPORT int getDefaultIndex() {
    return 1;
}