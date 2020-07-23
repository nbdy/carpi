//
// Created by insane on 23.07.20.
//

#include "SongItem.h"

SongItem::SongItem(const QString& path, QWidget *parent): path(path) {
    title = path.split("/").last().split(".").first();
    setText(title);
}

SongItem::~SongItem() {

}

QString SongItem::getPath() {
    return path;
}
