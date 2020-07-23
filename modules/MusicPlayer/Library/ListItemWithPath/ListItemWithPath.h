//
// Created by insane on 23.07.20.
//

#ifndef CARPI_QT_LISTITEMWITHPATH_H
#define CARPI_QT_LISTITEMWITHPATH_H

#include <QListWidgetItem>

class ListItemWithPath : public QListWidgetItem {
private:
    QString path;

public:
    ListItemWithPath(const QString& path);
    ~ListItemWithPath();

    QString getPath();
};


#endif //CARPI_QT_LISTITEMWITHPATH_H
