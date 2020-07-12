#include "Wireless.h"
#include "ui_wireless.h"


Wireless::Wireless(QWidget *parent): QWidget(parent), ui(new Ui::Wireless)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

Wireless::~Wireless()
{
    delete ui;
}

extern "C" WIRELESS_EXPORT QWidget* render() {
    return new Wireless();
}

extern "C" WIRELESS_EXPORT char* getName() {
    return (char*) "Wireless";
}

extern "C" WIRELESS_EXPORT int getDefaultIndex(){
    return 4;
}
