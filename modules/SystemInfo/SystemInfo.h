//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_SYSTEMINFO_H
#define CARPI_QT_SYSTEMINFO_H

#include "SystemInfo_global.h"

#include <QWidget>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class SystemInfo; }
QT_END_NAMESPACE

class SystemInfo : public QWidget
{
Q_OBJECT
private:
    Ui::SystemInfo *ui;

    QDateTime boot_time;

    QTimer *timer_critval;
    QTimer *timer_time;

private slots:
    void criticalValueSlot();
    void timeSlot();

public:
    explicit SystemInfo(QWidget *parent = nullptr);
    ~SystemInfo() override;
};

extern "C" {
    SYSTEMINFO_EXPORT int getDefaultIndex();
    SYSTEMINFO_EXPORT char* getName();
    SYSTEMINFO_EXPORT QWidget* render();
};


#endif //CARPI_QT_SYSTEMINFO_H
