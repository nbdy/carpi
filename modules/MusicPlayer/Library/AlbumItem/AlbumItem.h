//
// Created by insane on 23.07.20.
//

#ifndef CARPI_QT_ALBUMITEM_H
#define CARPI_QT_ALBUMITEM_H

#include "../ListItemWithPath/ListItemWithPath.h"

class AlbumItem : public ListItemWithPath {
public:
    AlbumItem(const QString& path);
    ~AlbumItem();

};


#endif //CARPI_QT_ALBUMITEM_H
