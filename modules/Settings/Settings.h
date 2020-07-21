#ifndef CARPI_QT_ISETTINGS_H
#define CARPI_QT_SETTINGS_H

#include "Settings_global.h"

#include "../../libs/ISettings/ISettings.h"
#include "SettingsTab/SettingsTab.h"
#include "../../libs/UI/VTabWidget/VTabWidget.h"

#include <QDebug>
#include <QWidget>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Settings; }
QT_END_NAMESPACE

class Settings : public QWidget
{
Q_OBJECT
private:
    Ui::Settings *ui;
    QGridLayout *layout;
    VTabWidget *vTabWidget;

    void populateTabs();

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings() override;
};

extern "C" {
    SETTINGS_EXPORT int getDefaultIndex();
    SETTINGS_EXPORT char* getName();
    SETTINGS_EXPORT QWidget* create();
};


#endif //CARPI_QT_ISETTINGS_H
