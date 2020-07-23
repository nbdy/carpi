//
// Created by insane on 23.07.20.
//

#include "ListItemWithPath.h"

ListItemWithPath::ListItemWithPath(const QString &path): path(path) {
    setText(path);
}

ListItemWithPath::~ListItemWithPath() {

}

QString ListItemWithPath::getPath() {
    return path;
}
