#ifndef CARPI_QT_WIFI_GLOBAL_H
#define CARPI_QT_WIFI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WIFI_LIBRARY)
#  define WIFI_EXPORT Q_DECL_EXPORT
#else
#  define WIFI_EXPORT Q_DECL_IMPORT
#endif

#endif //CARPI_QT_WIFI_GLOBAL_H
