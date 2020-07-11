//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_NAVIGATION_GLOBAL_H
#define CARPI_QT_NAVIGATION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NAVIGATION_LIBRARY)
#  define NAVIGATION_EXPORT Q_DECL_EXPORT
#else
#  define NAVIGATION_EXPORT Q_DECL_IMPORT
#endif

#endif //CARPI_QT_NAVIGATION_GLOBAL_H
