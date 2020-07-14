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
    bootTime = QDateTime::currentDateTime().toLocalTime();

    ui->wifi_mac->setText(Network::getMAC("wl"));
    ui->eth_mac->setText(Network::getMAC("eth"));
    ui->time_boot->setText(bootTime.toString("hh:mm:ss"));
    ui->date->setText(bootTime.toString("dd.MM.yyyy"));

    timerCritical = new QTimer(this);
    timerTime = new QTimer(this);

    connect(timerCritical, &QTimer::timeout, this, &SystemInfo::criticalValueSlot);
    connect(timerTime, &QTimer::timeout, this, &SystemInfo::timeSlot);

    timerCritical->start(420);
    timerTime->start(1000);
}

SystemInfo::~SystemInfo()
{
    timerTime->stop();
    timerCritical->stop();
    delete ui;
    delete timerTime;
    delete timerCritical;
}

void SystemInfo::criticalValueSlot() {
    ui->wifi_ip->setText(Network::getIP("wl"));
    ui->eth_ip->setText(Network::getIP("eth"));
    ui->cpu_temp->setText(QString::number(Utils::getCPUTemp()) + " °C");
}

void SystemInfo::timeSlot() {
    QDateTime t = QDateTime::currentDateTime().toLocalTime();
    ui->time_current->setText(t.toString("hh:mm:ss"));
    ui->time_run->setText(QDateTime::fromTime_t(t.toTime_t() - bootTime.toTime_t()).toLocalTime().toString("hh:mm:ss"));
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