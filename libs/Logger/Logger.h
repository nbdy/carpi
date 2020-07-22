//
// Created by insane on 21.07.20.
//

#ifndef CARPI_QT_LOGGER_H
#define CARPI_QT_LOGGER_H

#include <QDebug>
#include <QDateTime>

#define DATETIME_FORMAT "dd.MM.yyyy hh:mm:ss"
#define TAG_ERROR   " ERROR "
#define TAG_WARNING "WARNING"
#define TAG_INFO    " INFO  "
#define TAG_DEBUG   " DEBUG "

class Logger {
public:
    static void log(const QString& module, const QString& level, const QString& msg);
    static void error(const QString& module, const QString& msg);
    static void warning(const QString& module, const QString& msg);
    static void info(const QString& module, const QString& msg);
    static void debug(const QString& module, const QString& msg);
};


#endif //CARPI_QT_LOGGER_H
