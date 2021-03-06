//
// Created by insane on 12.07.20.
//

#ifndef CARPI_QT_MANAGER_H
#define CARPI_QT_MANAGER_H

#include "../Utils/Utils.h"
#include "../Logger/Logger.h"
#include "../ISettings/ISettings.h"
#include "../UI/VTabWidget/VTabWidget.h"
#include "../ModuleLoader/ModuleLoader.h"
#include "../UI/MainWindow/MainWindow.h"
#include <QApplication>
#include <QSettings>
#include <QDateTime>

#define KEY_GROUP_GENERAL "General"
#define KEY_MODULE_DIRECTORY "moduleDirectory"

class Manager {
private:
    QSettings *settings;
    ModuleLoader *loader;
    MainWindow *mainWindow;
    VTabWidget *vTabWidget;

    void setupUI();
    void attachTabs();
    void setDefaultSettings();
public:
    explicit Manager();
    ~Manager();
};


#endif //CARPI_QT_MANAGER_H
