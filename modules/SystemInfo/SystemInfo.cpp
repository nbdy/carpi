//
// Created by insane on 11.07.20.
//

#include "SystemInfo.h"

#include <QVBoxLayout>
#include <QtUiTools/QtUiTools>
#include <QFile>

extern "C" SYSTEMINFO_EXPORT QWidget* render() {
    auto *w = new QWidget();
    auto *l = new QVBoxLayout();

    // todo load ui file via qfile and quiloader

    w->setLayout(l);
    return w;
}

extern "C" SYSTEMINFO_EXPORT QString getName() {
    return "SystemInfo";
}



