//
// Created by insane on 11.07.20.
//

#include "SystemInfo.h"
#include "ui_systeminfo.h"


SystemInfo::SystemInfo(QWidget *parent): QMainWindow(parent), ui(new Ui::SystemInfo)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

SystemInfo::~SystemInfo()
{
    delete ui;
}

extern "C" SYSTEMINFO_EXPORT QWidget* render() {
    return new SystemInfo();
}

extern "C" SYSTEMINFO_EXPORT QString getName() {
    return "SystemInfo";
}



