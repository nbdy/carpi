
#include "Bluetooth.h"
#include "ui_bluetooth.h"


Bluetooth::Bluetooth(QWidget *parent): QMainWindow(parent), ui(new Ui::Bluetooth)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

Bluetooth::~Bluetooth()
{
    delete ui;
}

extern "C" BLUETOOTH_EXPORT QWidget* render() {
    return new Bluetooth();
}

extern "C" BLUETOOTH_EXPORT QString getName() {
    return "Bluetooth";
}
