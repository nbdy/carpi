//
// Created by insane on 23.07.20.
//

#ifndef CARPI_QT_SONGITEM_H
#define CARPI_QT_SONGITEM_H

#include <QListWidgetItem>

class SongItem : public QListWidgetItem {
private:
    QString path;
    QString title;

public:
    explicit SongItem(const QString& path, QWidget* parent = nullptr);
    ~SongItem();

    QString getPath();

};


#endif //CARPI_QT_SONGITEM_H
