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
    boot_time = QDateTime::currentDateTime();

    ui->wifi_mac->setText(Network::getMAC("wl"));
    ui->eth_mac->setText(Network::getMAC("eth"));
    ui->time_boot->setText(boot_time.toString("hh:mm:ss"));
    ui->date->setText(boot_time.toString("dd.MM.yyyy"));

    timer_critval = new QTimer(this);
    timer_time = new QTimer(this);

    connect(timer_critval, &QTimer::timeout, this, &SystemInfo::criticalValueSlot);
    connect(timer_time, &QTimer::timeout, this, &SystemInfo::timeSlot);

    timer_critval->start(420);
    timer_time->start(1000);
}

SystemInfo::~SystemInfo()
{
    timer_time->stop();
    timer_critval->stop();
    delete ui;
    delete timer_time;
    delete timer_critval;
}

void SystemInfo::criticalValueSlot() {
    ui->wifi_ip->setText(Network::getIP("wl"));
    ui->eth_ip->setText(Network::getIP("eth"));
    ui->cpu_temp->setText(QString::number(Utils::getCPUTemp()) + " °C");
}

void SystemInfo::timeSlot() {
    QDateTime t = QDateTime::currentDateTime();
    ui->time_current->setText(t.toString("hh:mm:ss"));
    ui->time_run->setText(QDateTime::fromMSecsSinceEpoch(boot_time.msecsTo(t) - 3600000).toString("hh:mm:ss"));
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