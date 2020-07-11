//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MUSICPLAYER_GLOBAL_H
#define CARPI_QT_MUSICPLAYER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MUSICPLAYER_LIBRARY)
#  define MUSICPLAYER_EXPORT Q_DECL_EXPORT
#else
#  define MUSICPLAYER_EXPORT Q_DECL_IMPORT
#endif

#endif //CARPI_QT_MUSICPLAYER_GLOBAL_H
