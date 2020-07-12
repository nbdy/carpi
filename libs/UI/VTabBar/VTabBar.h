//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_VTABBAR_H
#define CARPI_QT_VTABBAR_H

#include <QTabBar>

class VTabBar : public QTabBar
{
public:
    VTabBar();

    QSize tabSizeHint(int index) const override;
    void paintEvent(QPaintEvent *) override;
};


#endif //CARPI_QT_VTABBAR_H
