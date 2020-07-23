//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_NAVIGATION_H
#define CARPI_QT_NAVIGATION_H

#include "Navigation_global.h"

#include "../../libs/GPS/GPS.h"

#include <QWidget>
#include <QGridLayout>
#include <QtQuick/QQuickPaintedItem>

#include <osmscout/MapWidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Navigation; }
QT_END_NAMESPACE

class Navigation : public QWidget
{
Q_OBJECT
private:
    Ui::Navigation *ui;
    QGridLayout *gridLayout;
    GPS *gps;
    osmscout::OSMScoutQt *scout;

    std::shared_ptr<osmscout::DBThread> db;

public:
    explicit Navigation(QWidget *parent = nullptr);
    ~Navigation() override;
};

extern "C" {
    NAVIGATION_EXPORT int getDefaultIndex();
    NAVIGATION_EXPORT char* getName();
    NAVIGATION_EXPORT QWidget* create();
};


#endif //CARPI_QT_NAVIGATION_H
