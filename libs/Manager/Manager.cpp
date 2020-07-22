//
// Created by insane on 12.07.20.
//

#include "Manager.h"

Manager::Manager() {
    settings = ISettings::getSettings();
    setDefaultSettings();
    qDebug() << "the setting file lays here:" << settings->fileName();
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
        mainWindow->setWindowState(Qt::WindowFullScreen);
        mainWindow->setCursor(Qt::BlankCursor);
    }

    loader->loadAll();

    attachTabs();
    vTabWidget->show();

    mainWindow->setCentralWidget(vTabWidget);
    mainWindow->show();
}

void Manager::attachTabs() {

}

void Manager::setDefaultSettings() {
    if(settings->contains(KEY_GROUP_GENERAL)) return;
    qDebug() << "setting default general settings";
    settings->beginGroup(KEY_GROUP_GENERAL);
#ifdef DEBUG
    settings->setValue(KEY_MODULE_DIRECTORY, "./");
#else
    settings->setValue(KEY_MODULE_DIRECTORY, "/usr/local/lib/carpi/");
#endif
}
