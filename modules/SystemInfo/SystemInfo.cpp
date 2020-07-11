//
// Created by insane on 11.07.20.
//

#include "SystemInfo.h"
#include "ui_systeminfo.h"


SystemInfo::SystemInfo(QWidget *parent): QWidget(parent), ui(new Ui::SystemInfo)
{
    ui->setupUi(this);
}

SystemInfo::~SystemInfo()
{
    delete ui;
}

extern "C" SYSTEMINFO_EXPORT QWidget* render() {
    auto *w = new SystemInfo();


    return w;
}

extern "C" SYSTEMINFO_EXPORT QString getName() {
    return "SystemInfo";
}



