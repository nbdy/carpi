//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_NAVIGATION_H
#define CARPI_QT_NAVIGATION_H

#include "Navigation_global.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Navigation; }
QT_END_NAMESPACE

class Navigation : public QMainWindow
{
Q_OBJECT
private:
    Ui::Navigation *ui;

public:
    explicit Navigation(QWidget *parent = nullptr);
    ~Navigation() override;
};

extern "C" {
    NAVIGATION_EXPORT QString getName();
    NAVIGATION_EXPORT QWidget* render();
};


#endif //CARPI_QT_NAVIGATION_H
