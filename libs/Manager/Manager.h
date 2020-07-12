//
// Created by insane on 12.07.20.
//

#ifndef CARPI_QT_MANAGER_H
#define CARPI_QT_MANAGER_H

#include "../Utils/Utils.h"
#include "../UI/VTabWidget/VTabWidget.h"
#include "../ModuleLoader/ModuleLoader.h"
#include "../UI/MainWindow/MainWindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>

class Manager {
private:
    QSettings *settings;
    ModuleLoader *loader;
    MainWindow *mainWindow;
    VTabWidget *vTabWidget;

public:
    explicit Manager();

    ~Manager();

    void setupUI();
};


#endif //CARPI_QT_MANAGER_H
