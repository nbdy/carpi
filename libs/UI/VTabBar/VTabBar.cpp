//
// Created by insane on 11.07.20.
//

#include "VTabBar.h"

#include <QStylePainter>
#include <QStyleOptionTab>

VTabBar::VTabBar()
{

}

QSize VTabBar::tabSizeHint(int index) const
{
    QSize s = QTabBar::tabSizeHint(index);
    s.transpose();
    return s;
}

void VTabBar::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    QStyleOptionTab o;

    for (int i=0; i<count(); i++){
        initStyleOption(&o, i);
        p.drawControl(QStyle::CE_TabBarTabShape, o);
        p.save();

        QSize s = o.rect.size();
        s.transpose();
        QRect r(QPoint(), s);
        r.moveCenter(o.rect.center());
        o.rect = r;

        QPoint c = tabRect(i).center();
        p.translate(c);
        p.rotate(90);
        p.translate(-c);
        p.drawControl(QStyle::CE_TabBarTabLabel, o);
        p.restore();
    }
}