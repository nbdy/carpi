//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MODULELOADER_H
#define CARPI_QT_MODULELOADER_H

#include <QPair>
#include <QWidget>
#include <QString>
#include <QLibrary>
#include <QList>
#include <map>


class ModuleLoader {
private:
#ifdef DEBUG
    QString directory = "./";
#else
    QString directory = "/usr/local/lib/carpi/";
#endif

    QList<QLibrary*> libraries;
    QList<QPair<QWidget*, QString>*> widgets;

public:
    ModuleLoader();
    explicit ModuleLoader(const QString& directory);

    ~ModuleLoader();

    static QLibrary* load(const QString& name);
    void loadAll();

    template<typename R> static R executeReturn(QLibrary* lib, const QString& functionName);

    static QString getName(QLibrary* lib);
    static QWidget* getWidget(QLibrary* lib);

    QList<QPair<QWidget*, QString>*> getWidgets();
};


#endif //CARPI_QT_MODULELOADER_H
