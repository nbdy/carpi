//
// Created by insane on 12.07.20.
//

#include "Manager.h"

Manager::Manager() {
    loader = new ModuleLoader();
    mainWindow = new MainWindow();
    vTabWidget = new VTabWidget();
    setupUI();
}

Manager::Manager(const QString &moduleDirectory) {
    loader = new ModuleLoader(moduleDirectory);
    mainWindow = new MainWindow();
    vTabWidget = new VTabWidget();
    setupUI();
}

Manager::~Manager() {
    delete vTabWidget;
    delete loader;
    delete mainWindow;
}

void Manager::setupUI() {
    mainWindow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    if(Utils::isPi()) mainWindow->setWindowState(Qt::WindowFullScreen);

    loader->loadAll();

    for(const auto& p : loader->getWidgets()) {
        qDebug() << "attaching tab" << p->second;
        vTabWidget->addTab(p->first, p->second);
    }

    mainWindow->setCentralWidget(vTabWidget);
    vTabWidget->show();
    mainWindow->show();
}
