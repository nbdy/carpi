//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_SYSTEMINFO_H
#define CARPI_QT_SYSTEMINFO_H

#include "SystemInfo_global.h"
#include "../../libs/GPS/GPS.h"

#include <QGeoPositionInfo>
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
    const QString hourFormatStr = "hh:mm:ss";
    const QString dayFormatStr = "dd.MM.yyyy";

    Ui::SystemInfo *ui;

    GPS *gps;

    QDateTime bootTime;

    QTimer *timerCritical;
    QTimer *timerTime;

private slots:
    void gpsPositionOld(const QDateTime &ts);
    void gpsPositionChanged(const QGeoPositionInfo &info);
    void criticalValueSlot();
    void timeSlot();

public:
    explicit SystemInfo(QWidget *parent = nullptr);
    ~SystemInfo() override;
};

extern "C" {
    SYSTEMINFO_EXPORT int getDefaultIndex();
    SYSTEMINFO_EXPORT char* getName();
    SYSTEMINFO_EXPORT QWidget* create();
};


#endif //CARPI_QT_SYSTEMINFO_H
