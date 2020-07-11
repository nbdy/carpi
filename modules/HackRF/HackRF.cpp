#include "HackRF.h"
#include "ui_hackrf.h"


HackRF::HackRF(QWidget *parent): QMainWindow(parent), ui(new Ui::HackRF)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

HackRF::~HackRF()
{
    delete ui;
}

extern "C" HACKRF_EXPORT QWidget* render() {
    return new HackRF();
}

extern "C" HACKRF_EXPORT QString getName() {
    return "HackRF";
}
