//
// Created by insane on 21.07.20.
//

#include "Logger.h"

void Logger::log(const QString& module, const QString &level, const QString &msg) {
    qDebug() << "{" << QDateTime::currentDateTime().toString(DATETIME_FORMAT) << "} - [" << level << "] [" << module << "] > " << msg;
}

void Logger::error(const QString& module, const QString &msg) {
    log(module, TAG_ERROR, msg);
}

void Logger::warning(const QString& module, const QString &msg) {
    log(module, TAG_WARNING, msg);
}

void Logger::info(const QString& module, const QString &msg) {
    log(module, TAG_INFO, msg);
}

void Logger::debug(const QString& module, const QString &msg) {
    log(module, TAG_DEBUG, msg);
}
