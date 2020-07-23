//
// Created by insane on 11.07.20.
//

#include "Navigation.h"
#include "ui_navigation.h" // todo


Navigation::Navigation(QWidget *parent): QWidget(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    gridLayout = new QGridLayout(this);
    // todo set default settings
    gps = new GPS(this);
    // todo load settings

    osmscout::OSMScoutQt::RegisterQmlTypes();
    bool ok = osmscout::OSMScoutQt::NewInstance()
            .WithBasemapLookupDirectory("TODO") // todo
            .WithStyleSheetDirectory("TODO") // todo
            .WithIconDirectory("TODO") // todo
            .Init();

    if(!ok) Logger::error(getName(), "OSMScoutQt init failed"); // todo abort
    scout = &osmscout::OSMScoutQt::GetInstance();

    db = scout->GetDBThread();
    db->Initialize();

}

Navigation::~Navigation()
{
    delete ui;
}

extern "C" NAVIGATION_EXPORT QWidget* create() {
    return new Navigation();
}

extern "C" NAVIGATION_EXPORT char* getName() {
    return (char*) "Navigation";
}

extern "C" NAVIGATION_EXPORT int getDefaultIndex(){
    return 2;
}