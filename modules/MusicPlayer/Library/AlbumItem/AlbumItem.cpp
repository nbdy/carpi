//
// Created by insane on 23.07.20.
//

#include "AlbumItem.h"

AlbumItem::AlbumItem(const QString &path): ListItemWithPath(path) {
    setText(path.split("/").last());
}

AlbumItem::~AlbumItem() {

}
