#include "Settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent): QWidget(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
    layout = new QGridLayout(this);
    vTabWidget = new VTabWidget();
    layout->addWidget(vTabWidget);
    populateTabs();
    vTabWidget->show();

    connect(ui->btn_reload, SIGNAL(clicked()), this, SLOT(populateTabs()));
}

Settings::~Settings()
{
    delete vTabWidget;
    delete layout;
    delete ui;
}

void Settings::populateTabs() {
    vTabWidget->clear();
    for(const QString& k : ISettings::getSettings()->childGroups()){
        qDebug() << "adding setttings tab" << k;
        vTabWidget->addTab(new SettingsTab(k, this), k);
    }
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
