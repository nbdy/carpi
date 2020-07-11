//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_NAVIGATION_H
#define CARPI_QT_SYSTEMINFO_H

#include "SystemInfo_global.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SystemInfo; }
QT_END_NAMESPACE

class SystemInfo : public QMainWindow
{
Q_OBJECT
private:
    Ui::SystemInfo *ui;

public:
    explicit SystemInfo(QWidget *parent = nullptr);
    ~SystemInfo() override;
};

extern "C" {
    SYSTEMINFO_EXPORT QString getName();
    SYSTEMINFO_EXPORT QWidget* render();
};


#endif //CARPI_QT_NAVIGATION_H
