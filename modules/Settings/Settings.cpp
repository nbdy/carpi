#include "Settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent): QWidget(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

Settings::~Settings()
{
    delete ui;
}

extern "C" SETTINGS_EXPORT QWidget* create() {
    return new Settings();
}

extern "C" SETTINGS_EXPORT char* getName() {
    return (char*) "Settings";
}

extern "C" SETTINGS_EXPORT int getDefaultIndex(){
    return 0;
}
