//
// Created by insane on 11.07.20.
//

#include "Navigation.h"
#include "ui_navigation.h" // todo


Navigation::Navigation(QWidget *parent): QMainWindow(parent), ui(new Ui::Navigation)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

Navigation::~Navigation()
{
    delete ui;
}

extern "C" NAVIGATION_EXPORT QWidget* render() {
    return new Navigation();
}

extern "C" NAVIGATION_EXPORT QString getName() {
    return "Navigation";
}



