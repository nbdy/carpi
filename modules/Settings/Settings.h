#ifndef CARPI_QT_SETTINGS_H
#define CARPI_QT_SETTINGS_H

#include "Settings_global.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Settings; }
QT_END_NAMESPACE

class Settings : public QWidget
{
Q_OBJECT
private:
    Ui::Settings *ui;

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings() override;
};

extern "C" {
    SETTINGS_EXPORT int getDefaultIndex();
    SETTINGS_EXPORT char* getName();
    SETTINGS_EXPORT QWidget* render();
};


#endif //CARPI_QT_SETTINGS_H
