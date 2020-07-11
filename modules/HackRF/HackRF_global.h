#ifndef CARPI_QT_HACKRF_GLOBAL_H
#define CARPI_QT_HACKRF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HACKRF_LIBRARY)
#  define HACKRF_EXPORT Q_DECL_EXPORT
#else
#  define HACKRF_EXPORT Q_DECL_IMPORT
#endif

#endif //CARPI_QT_HACKRF_GLOBAL_H
