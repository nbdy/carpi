//
// Created by insane on 11.07.20.
//

#include "ModuleLoader.h"
#include <QDir>
#include <QDebug>

ModuleLoader::ModuleLoader()
{
    libraries = QList<QLibrary*>();
    widgets = QList<QPair<QWidget*, QString>*>();
}

ModuleLoader::ModuleLoader(const QString &directory)
{
    this->directory = directory;
    libraries = QList<QLibrary*>();
    widgets = QList<QPair<QWidget*, QString>*>();
}

ModuleLoader::~ModuleLoader()
{
    for(auto *lib : libraries) delete lib;
    for(auto *p : widgets) delete p;
}

QLibrary* ModuleLoader::load(const QString &name)
{
    auto *lib = new QLibrary(name.toStdString().c_str());
    if(lib->load()) {
        qDebug() << "loaded" << name;
        return lib;
    } else {
        qDebug() << "unable to load" << name;
        qDebug() << lib->errorString();
    }
    return nullptr;
}

void ModuleLoader::loadAll(){
    QDir dir(this->directory.toStdString().c_str());
    for(const auto& f : dir.entryList(QStringList() << "*.so", QDir::Files))
        this->libraries.append(this->load(dir.absoluteFilePath(f)));

    for(QLibrary *lib : libraries)
        widgets.append(new QPair<QWidget*, QString>(ModuleLoader::getWidget(lib), ModuleLoader::getName(lib)));

}

QList<QPair<QWidget*, QString>*> ModuleLoader::getWidgets() {
    return widgets;
}

QString ModuleLoader::getName(QLibrary *lib) {
    return executeReturn<char*>(lib, "getName");
}

QWidget *ModuleLoader::getWidget(QLibrary *lib) {
    return executeReturn<QWidget*>(lib, "render");
}

template<typename R>
R ModuleLoader::executeReturn(QLibrary *lib, const QString& functionName) {
    typedef R (*Function)();
    Function f = (Function) lib->resolve(functionName.toStdString().c_str());
    if(!f) qDebug() << lib->errorString();
    return f();
}