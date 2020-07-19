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
    gps = new GPS();
    bootTime = QDateTime::currentDateTime();

    ui->wifi_mac->setText(Network::getMAC("wl"));
    ui->eth_mac->setText(Network::getMAC("eth"));
    ui->time_boot->setText(bootTime.toString(hourFormatStr));
    ui->date->setText(bootTime.toString(dayFormatStr));

    timerCritical = new QTimer(this);
    timerTime = new QTimer(this);

    connect(gps, &GPS::positionChanged, this, &SystemInfo::gpsPositionChanged);
    connect(gps, &GPS::positionOld, this, &SystemInfo::gpsPositionOld);
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
    QDateTime t = QDateTime::currentDateTime();
    ui->time_current->setText(t.toString(hourFormatStr));
    QDateTime d = QDateTime::fromTime_t(t.toTime_t() - bootTime.toTime_t());
    ui->time_run->setText(QDateTime::fromTime_t(d.toTime_t()).toString(hourFormatStr)); // todo fix this showing 1 hour too much
}

void SystemInfo::gpsPositionChanged(const QGeoPositionInfo &info) {
    QGeoCoordinate c = info.coordinate();
    ui->gps_valid->setText("current");
    ui->gps_timestamp->setText(info.timestamp().toString(hourFormatStr));
    ui->latitude->setText(QString::number(c.latitude()));
    ui->longitude->setText(QString::number(c.longitude()));
    ui->altitude->setText(QString::number(c.altitude()));
}

void SystemInfo::gpsPositionOld(const QDateTime &ts) {
    ui->gps_valid->setText("old");
    ui->gps_timestamp->setText(ts.toString(hourFormatStr));
}

extern "C" SYSTEMINFO_EXPORT QWidget* create() {
    return new SystemInfo();
}

extern "C" SYSTEMINFO_EXPORT char* getName() {
    return (char*) "SystemInfo";
}

extern "C" SYSTEMINFO_EXPORT int getDefaultIndex() {
    return 1;
}

extern "C" SYSTEMINFO_EXPORT int getDependencies(){

}