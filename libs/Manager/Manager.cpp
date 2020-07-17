//
// Created by insane on 12.07.20.
//

#include "Manager.h"

Manager::Manager() {
    settings = new QSettings("eberlein", "carpi");
    qDebug() << "the setting file lays here:" << settings->fileName();
#ifdef DEBUG
    loader = new ModuleLoader(settings->value("moduleDirectory", "./").toString());
#else
    loader = new ModuleLoader(settings->value("moduleDirectory", "/usr/local/lib/carpi/").toString());
#endif
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
