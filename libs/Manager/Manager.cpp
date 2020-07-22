//
// Created by insane on 12.07.20.
//

#include "Manager.h"

Manager::Manager() {
    settings = ISettings::getSettings();
    setDefaultSettings();
    Logger::debug("Manager", "configuration file is here: " + settings->fileName());
    loader = new ModuleLoader(settings->value(KEY_MODULE_DIRECTORY).toString());
    mainWindow = new MainWindow();
    vTabWidget = new VTabWidget();
    setupUI();
}

Manager::~Manager() {
    delete vTabWidget;
    delete loader;
    delete mainWindow;
    delete settings;
}

void Manager::setupUI() {
    if(Utils::isPi()) {
        Logger::debug("Manager", "running on raspberry pi");
        Logger::info("Manager", "setting fullscreen");
        mainWindow->setWindowState(Qt::WindowFullScreen);
        Logger::info("Manager", "disabling cursor");
        mainWindow->setCursor(Qt::BlankCursor);
    }

    loader->loadAll();

    attachTabs();
    vTabWidget->show();

    mainWindow->setCentralWidget(vTabWidget);
    mainWindow->show();
}

void Manager::attachTabs() {
    Logger::debug("Manager", "attaching tabs");
    for(const auto& p : loader->getWidgets()) {
        if(settings->value(p->second, true).toBool()){
            Logger::debug("Manager", "attaching '" + p->second + "'");
            vTabWidget->addTab(p->first, p->second);
        }
    }
}

void Manager::setDefaultSettings() {
    if(settings->contains(KEY_GROUP_GENERAL)) return;
    Logger::debug("Manager", "setting default settings");
    settings->beginGroup(KEY_GROUP_GENERAL);
#ifdef DEBUG
    settings->setValue(KEY_MODULE_DIRECTORY, "./");
#else
    settings->setValue(KEY_MODULE_DIRECTORY, "/usr/local/lib/carpi/");
#endif
}
