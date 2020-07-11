#include <iostream>

#include <QtDebug>
#include <QApplication>

#include "libs/ModuleLoader/ModuleLoader.h"
#include "libs/UI/VTabWidget/VTabWidget.h"
#include "libs/Utils/Utils.h"
#include "libs/UI/MainWindow/MainWindow.h"

void setupTabs(MainWindow *m){
    qDebug() << "setting up tabs";
    auto *w = new VTabWidget();

    auto *mloader = new ModuleLoader();
    mloader->loadAll();

    for(auto p : *mloader->getWidgets()){
        qDebug() << "adding tab" << p->second;
        w->addTab(p->first, p->second);
    }

    w->show();
    m->setCentralWidget(w);
}

int main(int argc, char **argv) {
    qDebug() << "starting";
    QApplication a(argc, argv);
    auto *w = new MainWindow();
    qDebug() << "setting window flags";
    w->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    if(Utils::isPi()) w->setWindowState(Qt::WindowFullScreen);
    setupTabs(w);
    qDebug() << "showing and executing";
    w->show();
    return QApplication::exec();
}
