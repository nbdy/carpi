//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_SYSTEMINFO_GLOBAL_H
#define CARPI_QT_SYSTEMINFO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SYSTEMINFO_LIBRARY)
#  define SYSTEMINFO_EXPORT Q_DECL_EXPORT
#else
#  define SYSTEMINFO_EXPORT Q_DECL_IMPORT
#endif

#endif //CARPI_QT_SYSTEMINFO_GLOBAL_H
