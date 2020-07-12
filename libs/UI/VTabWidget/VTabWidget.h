//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_VTABWIDGET_H
#define CARPI_QT_VTABWIDGET_H

#include <QTabWidget>

class VTabWidget : public QTabWidget
{
private:
    int tabHeight = 200;
    int tabWidth = 50;

    void _setStyleSheet();

public:
    VTabWidget();
    VTabWidget(int tabHeight, int tabWidth);
};


#endif //CARPI_QT_VTABWIDGET_H
