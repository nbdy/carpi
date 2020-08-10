//
// Created by insane on 05.08.20.
//

#include "IsFile.h"

IsFile::IsFile(QObject *parent) : QObject(parent) {

}

void IsFile::setFile(const QUrl& file) {
    this->file = file;
    emit fileChanged();
}

bool IsFile::isFile() const {
    return QFile::exists(file.toLocalFile());
}

IsFile::~IsFile() {

}

QUrl IsFile::getFile() const {
    return this->file;
}